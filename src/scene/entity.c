#include "entity.h"
#include "scene.h"

Entity entity_create(int id, vec3s pos, float rotation, float scale,  Entity_Flags flags) {
  Entity self = {.id = id, .position = pos, .rotation = rotation, .scale = scale};

  self.flags = flags;

  if (flags.isPlayer) {
    self.velocity = 0;
    self.maxVelocity = 10;
    self.acceleration = 0.5f;
  }

  if (flags.isAstroid) {
    self.velocity = 0;
    self.maxVelocity = 10;
    self.acceleration = 0.5f;
  }
  if (flags.isBullet) {
    self.velocity = 200;
  }

  entity_update_ModelMat(&self);
  return self;
}

void entity_move(Entity *self, vec3s offset) {
  self->position = glms_vec3_add(self->position, offset);
  entity_update_ModelMat(self);
}
void entity_rotate(Entity *self, float angle) {
  self->rotation += angle;
  if (self->rotation > 359)
    self->rotation = 0;
  entity_update_ModelMat(self);
}

void entity_scale(Entity *self, float scale) {
  self->scale += scale;
  entity_update_ModelMat(self);
}

void entity_update_ModelMat(Entity *self) {
  self->modelMat = glms_mat4_identity();
  self->modelMat = glms_translate(self->modelMat, self->position);
  self->modelMat =
      glms_rotate(self->modelMat, glm_rad(self->rotation), (vec3s){{0, 0, 1}});
  self->modelMat = glms_scale_uni(self->modelMat, self->scale);

  self->front.x = cos(glm_rad(self->rotation - 90));
  self->front.y = sin(glm_rad(self->rotation - 90));
}

void entity_addSprite(Entity *self, float *vertices, u32 vsize, u32 *elements,
                      u32 esize, vec2s size) {
  self->size = size;
  glCreateVertexArrays(1, &self->vao);
  glBindVertexArray(self->vao);

  glGenBuffers(1, &self->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
  glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &self->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, esize, elements, GL_STATIC_DRAW);
  self->numelements = 6;

  glBindVertexArray(0);

  self->flags.hasSprite = true;
}

static vec2s lastFront = {};
static float storedVelocity = 0;

void _update_player(Entity *self) {
  // todo update this later
  // movement
  if (window.key[GLFW_KEY_UP].down) {
    if (window.key[GLFW_KEY_UP].pressed)
      self->velocity = 0;

    storedVelocity -= 0.5 * window.deltaTime;

    vec3s lastOffset = glms_vec3_scale((vec3s){{lastFront.x, lastFront.y, 0}},
                                       GLM_MAX(storedVelocity, 0));

    self->velocity += self->acceleration * window.deltaTime;
    vec3s curOffset =
        glms_vec3_scale((vec3s){{self->front.x, self->front.y, 0}},
                        GLM_MIN(self->velocity, self->maxVelocity));

    vec3s finalOffset = glms_vec3_add(lastOffset, curOffset);

    entity_move(self, finalOffset);
    lastFront = self->front;

  } // deceleration
  else {
    self->velocity -= 0.5f * window.deltaTime;
    self->velocity = GLM_MAX(self->velocity, 0);
    vec3s offset =
        glms_vec3_scale((vec3s){{lastFront.x, lastFront.y, 0}}, self->velocity);

    entity_move(self, offset);
    storedVelocity = self->velocity / 2;
  }
  // rotation
  float speed = 200 * window.deltaTime;
  if (window.key[GLFW_KEY_LEFT].down) {
    entity_rotate(self, -speed);
  }
  if (window.key[GLFW_KEY_RIGHT].down) {
    entity_rotate(self, speed);
  }

  // shooting
  if (window.key[GLFW_KEY_SPACE].down) {
    Entity *e = scene_addEntity((Entity_Flags){true, false, false, true});
    
  }
}
void _update_bullet(Entity *self) {
  float speed = self->velocity * window.deltaTime;
  vec3s offset =
      glms_vec3_scale((vec3s){{self->front.x, self->front.y, 0}}, speed);
  entity_move(self, offset);
}
void entity_update(Entity *self) {
  if (self->flags.isPlayer) {
    _update_player(self);
  }
  else if(self->flags.isBullet){
    _update_bullet(self);
  }

  vec2s edgeOne = glms_vec2_scale((vec2s){{-50, -50}}, self->scale);
  vec2s edgeTwo = glms_vec2_scale(
      (vec2s){{window.size.x + 50, window.size.y + 50}}, self->scale);

  if (self->position.x < edgeOne.x) {
    self->position.x = edgeTwo.x - 10;
  }
  if (self->position.y < edgeOne.y) {
    self->position.y = edgeTwo.y - 10;
  }
  if (self->position.x > edgeTwo.x) {
    self->position.x = edgeOne.x + 10;
  }
  if (self->position.y > edgeTwo.y) {
    self->position.y = edgeOne.y + 10;
  }
}

void entity_delete(Entity *self) {
  if (self->flags.hasSprite) {
    glDeleteBuffers(1, &self->ebo);
    glDeleteBuffers(1, &self->vbo);
    glDeleteVertexArrays(1, &self->vao);
  }
  self = NULL;
}
