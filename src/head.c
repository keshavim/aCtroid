#include "head.h"

head* head_create(int v1, int v2, int v3)
{
    
    head* self = calloc(1, sizeof *self);

    self->var1 = v1;
    self->var2 = v2;
    self->var3 = v3;

    return self;
}

void head_print(head* self)
{
    
    printf("head{v1 = %d,v2 = %d, v3 = %d}", self->var1, self->var2, self->var3);
}
head* head_get(head* self){
    return self;
}
