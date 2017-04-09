#include "stdio.h" 

int main(void) 
{ 
	int color;
	for (color = 0; color < 20; color++) 
	{ 
		printf("\033[1;4;%dmThe   color   of   this   line   is   %d,   %s!\033[0m\n", 30+color, 30+color, "ha   ha");
	} 
	return 0;
}
