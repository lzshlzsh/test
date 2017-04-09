#include <stdio.h>

typedef struct 
{
	union{
		unsigned int value[3];
		struct{
			unsigned int addr;
			unsigned int size;
			int offset;
		};
	};
}BP_Mem;

int main()
{
	BP_Mem m;

	m.value[0] = 1;
	m.value[1] = 2;
	m.value[2] = 3;

	printf("%d %d %d\n", m.addr, m.size, m.offset);

	return 0;
}
