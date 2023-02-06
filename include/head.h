#ifndef HEAD_H
#define HEAD_H

#include <stdlib.h>
#include <stdio.h>

typedef struct head{
    int var1;
    int var2;
    int var3;
} head;


extern head* head_create(int v1, int v2, int v3);

extern void head_print(head* self);
extern head* head_get(head* self);

#endif // HEAD_H
