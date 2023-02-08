#ifndef ENTITY_H
#define ENTITY_H
#include "gfx.h"

typedef struct {
  struct {
    vec3s position;
    float rotation;
    float scale;
    mat4s modelMat;
  };

  struct {
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 numelements;
  };
} Entity;

Entity entity_create(vec3s pos);
void entity_move(Entity *self, vec3s offset);
void entity_rotate(Entity *self, float angle);
void entity_scale(Entity *self, float scale);
void entity_update_ModelMat(Entity *self);

void entity_addSprite(Entity *self, float *vertex, u32 vsize, u32 *element,
                      u32 esize);
void entity_update(Entity *self);

#endif // ENTITY_H
