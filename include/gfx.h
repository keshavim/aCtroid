#ifndef GFX_H
#define GFX_H

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/struct.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

// window
// todo improve input detection
typedef struct {
  bool down, pressed;
} Button;

typedef struct {
  GLFWwindow *handle;
  ivec2s size;
  s8 *title;

  // this is completely unnessacery but it looks cool so i'm keeping it

  Button key[GLFW_KEY_LAST];
  Button mouse[GLFW_MOUSE_BUTTON_LAST];

  float currentTime, lastTime, deltaTime, fps;
} Window;
// global window
extern Window window;

void window_init();
void window_loop();

// shader

typedef struct {
  u32 program;
  char *filepath;
} Shader;

Shader shader_create(char *filepath);
void shader_bind(Shader *self);
void shader_unbind();
void shader_delete(Shader *self);

void shader_setUniformi(Shader *self, char *name, s32 val);
void shader_setUniform1f(Shader *self, char *name, float val);
void shader_setUniform2f(Shader *self, char *name, vec2s val);
void shader_setUniform3f(Shader *self, char *name, vec3s val);
void shader_setUniform4f(Shader *self, char *name, vec4s val);

void shader_setUniform_mat4(Shader *self, char *name, mat4s val);

// renderer

typedef struct {
  Shader shader;
  u32 vao, vbo, ebo, numElements;

  vec4s clear_color;
} Renderer;

void renderer_init(Renderer *self);
void renderer_prepare(Renderer *self);
void renderer_render(Renderer *self);
void renderer_delete(Renderer *self);

// camera
typedef struct {
  vec2s position;
  mat4s viewMat;
  mat4s projMat;
} Camera;

void camera_init(Camera *self, vec2s position);

void camera_update(Camera *self);

#endif // GFX_H
