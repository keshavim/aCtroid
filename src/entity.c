#include "entity.h"

Entity entity_create(vec3s pos) {
  Entity self = {{.position = pos, .rotation = 0, .scale = 2}, {0}};

  entity_update_ModelMat(&self);
  return self;
}

void entity_move(Entity *self, vec3s offset) {
  self->position = glms_vec3_add(self->position, offset);
  entity_update_ModelMat(self);
}

void entity_rotate(Entity *self, float angle) {
  self->rotation += angle;
  if(self->rotation > 359) self->rotation = 0;
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
      glms_rotate_at(self->modelMat,(vec3s){{0, 0, 0}}, self->rotation, (vec3s){{0, 0, 1}});
  self->modelMat = glms_scale_uni(self->modelMat, self->scale);
}

void entity_addSprite(Entity *self, float *vertices, u32 vsize, u32 *elements,
                      u32 esize) {
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
}

void entity_update(Entity *self) {
    float speed = 100 * window.deltaTime;
  if (window.key[GLFW_KEY_LEFT].down) {
    entity_move(self, (vec3s){{-speed, 0, 0}});
  }
  if (window.key[GLFW_KEY_RIGHT].down) {
    entity_move(self, (vec3s){{speed, 0, 0}});
  }
  if (window.key[GLFW_KEY_UP].down) {
    entity_move(self, (vec3s){{0, -speed, 0}});
  }
  if (window.key[GLFW_KEY_DOWN].down) {
    entity_move(self, (vec3s){{0, speed, 0}});
  }
    speed = 5 * window.deltaTime;
  if(window.key[GLFW_KEY_A].down){
    entity_rotate(self, -speed);
  }
  if(window.key[GLFW_KEY_D].down){
    entity_rotate(self, speed);
  }
  if(window.key[GLFW_KEY_S].down){
    entity_scale(self, -speed);
  }
  if(window.key[GLFW_KEY_W].down){
    entity_scale(self, speed);
  }
}
