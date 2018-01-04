#include <stdio.h>


typedef enum Color_ColorEnum{ RED, GREEN, DEFAULT } Color_ColorEnum;

void Color_setColor_Color_ColorEnum(Color_ColorEnum color){
	const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	puts(pallete[color]);
}

struct Color {
};


typedef void (*vptr_t)(void);

void Scaleable_DTOR() { }
void Scaleable_scale_double(double);
vptr_t vtable_Scaleable[] = { (vptr_t)Scaleable_DTOR, (vptr_t)Scaleable_scale_double };

int
main (int argc, char *argv[])
{
    Color_setColor_Color_ColorEnum(RED);
    
    return 0;
}


