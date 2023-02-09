#include "scene.h"

Scene scene;

#define SPAWN_RATE 3;
static float spawnTimer = SPAWN_RATE;

float vertices[] = {-50.0, 50.0, 0.0, 50.0, 50.0, 0.0, 0.0, -50.0, 0.0};
u32 elements[] = {0, 1, 2};

void scene_init() {
  scene.window = &window;
  renderer_init(&scene.renderer);
  camera_init(&scene.camera, (vec2s){{2, 0}});

  scene.numEntities = 0;

  Entity_Flags f = {true, true, false, false};
  scene_addEntity(f);
}

void scene_render() {
  renderer_prepare(&scene.renderer);
  renderer_render(&scene.renderer);
}
void scene_update() {
  camera_update(&scene.camera);

  for (int i = 0; i < MAX_ENTITIES; i++) {
    entity_update(&scene.entities[i]);
  }
  // spawnTimer -= window.deltaTime;

  // if (spawnTimer < 0) {
  //   spawnTimer = SPAWN_RATE;
  //   scene_addEntity((Entity_Flags){true, false, true, false});
  // }
}

void scene_delete() {
  renderer_delete(&scene.renderer);
  while (scene.numEntities-- > 0) {
    entity_delete(&scene.entities[scene.numEntities]);
  }
}
// creating etities by the template flags
Entity *scene_addEntity(Entity_Flags flags) {

  if (scene.numEntities == MAX_ENTITIES) {
    scene_removeEntity(scene.numEntities - 1);
    return NULL;
  }
  vec3s pos = {{0}};
  float rotation = 0;
  float scale = 1;
  if (flags.isPlayer) {
    pos.x =window.size.x / 2.0f;
    pos.y = window.size.y / 2.0f;
    pos.z = 0;
  } 
  else if (flags.isAstroid) {
    pos = (vec3s){
        {RANDOM(10, window.size.x - 10), RANDOM(10, window.size.y - 10), 0}};
    rotation = RANDOM(0, 359);
  } 
  else if (flags.isBullet) {
    pos= scene.entities[0].position;
    rotation = scene.entities[0].rotation;
    scale = 0.5f;
  }
  scene.entities[scene.numEntities] =
      entity_create(scene.numEntities, pos,rotation, scale, flags);
  if (flags.hasSprite)
    entity_addSprite(&scene.entities[scene.numEntities], vertices,
                     sizeof vertices, elements, sizeof elements,
                     (vec2s){{0, 0}});

  Entity *temp = &scene.entities[scene.numEntities];

  scene.numEntities++;

  return temp;
}
void scene_removeEntity(int id) {
  if (id > scene.numEntities || id < 0)
    return;

  entity_delete(&scene.entities[id]);
  for (int i = id; i < scene.numEntities; i++) {
    scene.entities[i] = scene.entities[i + 1];
  }
  scene.numEntities--;
}