#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>


typedef  struct{
    GLFWwindow *handle;
    int width, height;
    char *title;
} Window;
//global window
extern Window window;

void window_create();
void window_loop();

#endif // WINDOW_H
