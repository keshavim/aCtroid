#ifndef ENTITY_H
#define ENTITY_H
#include "gfx.h"

typedef struct Entity_Flags {
  bool hasSprite;
  bool isPlayer;
  bool isAstroid;
} Entity_Flags;

typedef struct {
  int id;

  // transform
  struct {
    mat4s modelMat;
    vec3s position;
    vec2s front;
    vec2s lastFront;
    float rotation;
    float scale;
  };
  // sprite
  struct {
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 numelements;
    vec2s size;
  };
  struct {
    float velocity;
    float maxVelocity;
    float acceleration;
  };
  Entity_Flags flags;
} Entity;

Entity entity_create(int id, vec3s pos, Entity_Flags flags);

void entity_move(Entity *self, vec3s offset);
void entity_rotate(Entity *self, float angle);
void entity_scale(Entity *self, float scale);
void entity_update_ModelMat(Entity *self);

void entity_addSprite(Entity *self, float *vertex, u32 vsize, u32 *element,
                      u32 esize, vec2s size);

void entity_update(Entity *self);
void entity_delete(Entity *self);
#endif // ENTITY_H
