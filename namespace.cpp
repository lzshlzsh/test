/**
 *	Created Time: 2009-09-08 09:02:41
 *	Last Modified: 2009-09-08 09:02:41
 *	File Name: namespace.c
 *	Description: 
 */
#include <stdio.h>


namespace Test
{
	void foo();
	void foo1();
}

void Test::foo()
{
	printf("foo():in\n");
}

namespace Test
{
	void foo1()
	{
		printf("foo1():in\n");
	}
}

void foo()
{
	printf("foo():out\n");
}
void foo1()
{
	printf("foo1():out\n");
}

int main()
{
	Test::foo();
	for (int i = 0; i < 1; i++){
		using Test::foo1;
//		using namespace Test; //ambiguous func foo1()
		foo1();
	}

	if (1){
		using Test::foo;
		foo();
	}
	foo();
	return 0;
}
