#include "gfx.h"
#include "scene.h"
void renderer_init(Renderer *self) {
  *self = (Renderer){0};
  self->shader = shader_create("assets/def.glsl");
  self->clear_color = (vec4s){{0.0, 0.0, 0.0, 1}};

  // todo: move this stuff in to a sprite struct
}
void renderer_prepare(Renderer *self) {
  glClearColor(self->clear_color.x, self->clear_color.y, self->clear_color.z,
               self->clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_render(Renderer *self) {
  shader_bind(&self->shader);

  shader_setUniform_mat4(&self->shader, "viewMat", scene.camera.viewMat);
  shader_setUniform_mat4(&self->shader, "projMat", scene.camera.projMat);

  for (int i = 0; i < scene.numEntities; i++) {
    Entity *e = &scene.entities[i];
    if (e->flags.hasSprite) {

      shader_setUniform_mat4(&self->shader, "modelMat", e->modelMat);
      glBindVertexArray(e->vao);
      glDrawElements(GL_TRIANGLES, e->numelements, GL_UNSIGNED_INT, NULL);
    }
  }
}

void renderer_delete(Renderer *self) {
  shader_delete(&self->shader);
  glDeleteBuffers(1, &self->vbo);
  glDeleteBuffers(1, &self->ebo);
  glDeleteVertexArrays(1, &self->vao);
}
