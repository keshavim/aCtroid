#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "gfx.h"

#define MAX_ENTITIES 1

typedef struct {
  Window *window;
  Renderer renderer;
  Camera camera;
  Entity entities[MAX_ENTITIES];
} Scene;

extern Scene scene;

#endif // SCENE_H
