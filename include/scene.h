#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "gfx.h"

#define MAX_ENTITIES 10


typedef struct {
  Window *window;
  Renderer renderer;
  Camera camera;
  Entity entities[MAX_ENTITIES+1];
  int numEntities;
} Scene;

extern Scene scene;


void scene_init();

void scene_render();

void scene_update();

void scene_delete();

void scene_addEntity(Entity_Flags flags);
void scene_removeEntity(int id);

#endif // SCENE_H
