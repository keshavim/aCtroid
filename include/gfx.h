#ifndef GFX_H
#define GFX_H

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/types-struct.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"

//window
typedef struct{
    bool down;
}Button;

typedef  struct{
    GLFWwindow *handle;
    ivec2s size;
    s8 *title;

    Button keys[GLFW_KEY_LAST];
    Button mouse[GLFW_MOUSE_BUTTON_LAST];
} Window;
//global window
extern Window window;

void window_create();
void window_loop();


//shader

typedef struct {
    u32 program;
    char *filepath;
    u32 vs_handle;
    u32 fs_handle;
    char *vertex_source;
    char *fragment_source;
}Shader;

Shader shader_create(char *filepath);
void shader_bind(Shader *self);
void shader_unbind(Shader *self);
void shader_delete(Shader *self);

//renderer

#endif // GFX_H
