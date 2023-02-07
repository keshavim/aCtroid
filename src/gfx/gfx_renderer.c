#include "gfx.h"

void renderer_create(Renderer *self){
    self->shader = shader_create("assets/def.glsl");

    glCreateVertexArrays(1, &self->vao);
    glBindVertexArray(self->vao);

    glGenBuffers(1, &self->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER, (3 *4) * sizeof(float),(float[]){
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
        1, 0, 0,
    }, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glGenBuffers(1, &self->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6)*sizeof(u32), (u32[]){
        3, 0, 1, 3, 1, 2
    },GL_STATIC_DRAW);
    self->numElements = 6;


    glBindVertexArray(0);
}
void renderer_draw_square(Renderer *self){
    shader_bind(&self->shader);
    glBindVertexArray(self->vao);
    glDrawElements(GL_TRIANGLES, self->numElements, GL_UNSIGNED_INT, NULL);
}