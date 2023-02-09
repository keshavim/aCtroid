#include "scene.h"

Scene scene;

#define SPAWN_RATE 5;
static float spawnTimer = SPAWN_RATE;

float vertices[] = {-50.0, 50.0, 0.0, 50.0, 50.0, 0.0, 0.0, -50.0, 0.0};
u32 elements[] = {0, 1, 2};

void scene_init() {
  scene.window = &window;
  renderer_init(&scene.renderer);
  camera_init(&scene.camera, (vec2s){{2, 0}});

  scene.numEntities = 0;

  scene_addEntity((Entity_Flags){true, true, false});
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
  spawnTimer -= window.deltaTime;

  if (spawnTimer < 0) {
    spawnTimer = SPAWN_RATE;
    scene_addEntity((Entity_Flags){true, false, true});
  }
}

void scene_delete() {
    renderer_delete(&scene.renderer);
    while(scene.numEntities-- > 0){
        entity_delete(&scene.entities[scene.numEntities]);
    }

}

void scene_addEntity(Entity_Flags flags) {
  
  if (scene.numEntities == MAX_ENTITIES)
    return;
  if (flags.isPlayer) {
    scene.entities[scene.numEntities] = entity_create(
        scene.numEntities,
        (vec3s){{window.size.x / 2.0f, window.size.y / 2.0f, 0}}, flags);

    entity_addSprite(&scene.entities[scene.numEntities], vertices,
                     sizeof vertices, elements, sizeof elements,
                     (vec2s){{0, 0}});

  } else if (flags.isAstroid) {
    scene.entities[scene.numEntities] = entity_create(
        scene.numEntities,
        (vec3s){{RANDOM(10, window.size.x-10), RANDOM(10, window.size.y-10), 0}},
        flags);

    entity_addSprite(&scene.entities[scene.numEntities], vertices,
                     sizeof vertices, elements, sizeof elements,
                     (vec2s){{0, 0}});
   
  }
 

  scene.numEntities++;
}
void scene_removeEntity(int id){
    if(id > scene.numEntities || id < 0) return;
    
}