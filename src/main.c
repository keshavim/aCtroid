

#include "gfx.h"
#include "scene.h"

Scene scene;

float vertices[] = {
    0.0, 0, 0, 0, 100, 0, 100, 100, 0, 100, 0, 0,
};
u32 elements[] = {3, 0, 1, 3, 1, 2};

static void _init() {
  scene.window = &window;
  renderer_init(&scene.renderer);
  camera_init(&scene.camera, (vec2s){{2, 0}});
  for (int i = 0; i < MAX_ENTITIES; i++) {
    scene.entities[i] = entity_create((vec3s){{0, 0, 0}});
    entity_addSprite(&scene.entities[i], vertices, sizeof vertices, elements,
                     sizeof elements);
  }
}

static void _render() {
  renderer_prepare(&scene.renderer);
  renderer_render(&scene.renderer);
}
static void _update() {
  camera_update(&scene.camera);

  for (int i = 0; i < MAX_ENTITIES; i++) {
    entity_update(&scene.entities[i]);
  }
}

static void _delete() { renderer_delete(&scene.renderer); }

int main() {
  window_init(_init, _update, _render, _delete);
  window_loop();

  return 0;
}