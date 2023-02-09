
#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

uniform mat4 modelMat, viewMat, projMat;

void main()
{
    gl_Position = projMat *viewMat * modelMat* vec4(aPos, 1.0); //projMat * viewMat* see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(1.0,1.0, 1.0, 1.0); // set the output variable to a dark-red color
}
//VERTEX_END

#version 450 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
} 
//FRAGMENT_END