#include <stdio.h>
#include <assert.h>


#define STACK_SIZE 1024
/*
 * use idx [1..size-1]
 */
static char __s[STACK_SIZE]; 
static int __idx = 0;

static void __push_back(const char s)
{
	assert(__idx < STACK_SIZE);	
	__s[++__idx] = s;
}

static char __pop()
{
	assert(__idx > 0);
	return __s[__idx--];
}

static int __empty()
{
	return (0 == __idx);
}

static void __clear()
{
	__idx = 0;
}

typedef struct stack
{
	void (*push_back)(const char s);
	char (*pop)();
	int (*empty)();
	void (*clear)();
}stack;

static struct stack stack_default = {
	__push_back, __pop, __empty, __clear
};

static int check_bracket(const char *str)
{
	stack s = stack_default;	

	s.clear();

	while (*str && '(' != *str && ')' != *str){str++;}
	if (! *str)
		return 1;
	if (')' == *str)
		return 0;

	s.push_back(*str);
	str++;

	while (*str){
		if (')' == *str){
			if (s.empty())
				return 0;
			s.pop();
		}else if ('(' == *str){
			s.push_back(*str);
		}
		str++;
	}
	
	if (!s.empty())
		return 0;

	return 1;
}


int main()
{
	char str[1024];
	int match;

	do{
		printf("input an expression with bracket, input q(Q) to quit\n: ");
		scanf("%s", str);
		match = check_bracket(str);
		if ('q' == str[0] || 'Q' == str[0])
			break;
		if (match)
			printf("backets match\n");
		else
			printf("backets NOT match\n");
	}while (1);

	return 0;
}
