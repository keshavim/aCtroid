#include "gfx.h"

void camera_init(Camera *self, vec2s position) {
  self->position = position;
  camera_update(self);
}

void camera_update(Camera *self) {

  vec3s target = {{0, 0, 1}};

  self->viewMat = glms_mat4_identity();
  self->viewMat = glms_lookat(
      (vec3s){{self->position.x, self->position.y, 20.0}},
      glms_vec3_add(target, (vec3s){{self->position.x, self->position.y, 0.0}}),
      (vec3s){{0, 1, 0}});

  self->projMat = glms_mat4_identity();
  self->projMat =
      glms_ortho(0.0f, window.size.x, window.size.y, 0, 0.0f, 100.0f);
}
