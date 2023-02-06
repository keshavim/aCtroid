
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
static void framebuffer_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

static void GLAPIENTRY debugMessage_callback(GLenum source, GLenum type,
                                             GLuint id, GLenum severity,
                                             GLsizei length,
                                             const GLchar *message,
                                             const void *userParam) {

  char *sourcestr, *typestr, *severitystr;
  switch (source) {
  case GL_DEBUG_SOURCE_API:
    sourcestr = "Source: API";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    sourcestr = "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    sourcestr = "Source: Other";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    sourcestr = "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    sourcestr = "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    sourcestr = "Source: Window System";
    break;
  }

  switch (type) {
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    typestr = "Type: Deprecated Behavior";
    break;
  case GL_DEBUG_TYPE_ERROR:
    typestr = "Type: Error";
    break;
  case GL_DEBUG_TYPE_MARKER:
    typestr = "Type: Marker";
    break;
  case GL_DEBUG_TYPE_OTHER:
    typestr = "Type: Other";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    typestr = "Type: Performance";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    typestr = "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    typestr = "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    typestr = "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    typestr = "Type: Undefined Behavior";
    break;
  }
  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    severitystr = "Severity High";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    severitystr = "Severity Low";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    severitystr = "Severity Medium";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    severitystr = "Severity Notification";
    break;
  }
  fprintf(stderr, "\n\n--error--\nGL_OUTPUT: %s\n%s\n%s\n%s\n--error--\n",
          message, typestr, sourcestr, severitystr);
  //free((char*)userParam);
}

#pragma GCC diagnostic pop;

int main(void) {

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  GLFWwindow *window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window) {
  glfwTerminate();
    exit(EXIT_FAILURE);
  }
  

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(debugMessage_callback, NULL);

  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
