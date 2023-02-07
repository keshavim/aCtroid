#include "window.h"

Window window;


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{

    char *sourcestr, *typestr, *severitystr;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             sourcestr = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourcestr = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourcestr = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourcestr = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourcestr = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           sourcestr = "Source: Other"; break;
    } 

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:                typestr = "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:  typestr = "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:   typestr = "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:          typestr = "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:          typestr = "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:               typestr = "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:           typestr = "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:            typestr = "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:                typestr = "Type: Other"; break;
    }
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         severitystr = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severitystr = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severitystr = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severitystr = "Severity: notification"; break;
    } 
    
    fprintf(stderr, "----GL_Output---\nGL_Message: %s\n%s\n%s\n%s",message,typestr,sourcestr, severitystr);
}

void window_create(){
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit()){
        exit(EXIT_FAILURE);

	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); 


    /* Create a windowed mode window and its OpenGL context */
    window.handle = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window.handle)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
        
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window.handle);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, NULL);
}

void window_loop(){
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.handle))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.handle);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
