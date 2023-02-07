

#include "gfx.h"

int main()
{
	window_create();
	Shader shader = shader_create("assets/def.glsl");
	window_loop();

    
    return 0;
}