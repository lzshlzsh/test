
int main()
{
	int a, b;
	asm volatile(
	"movl $0x0, %%ebx	\n"
	"leal %0, %%ecx	\n"
	"movl $0x4, %%edx	\n"
	"movl $0x3, %%eax	\n"
	"int $0x80	\n"

	"leal %1, %%ecx	\n"
	"movl $0x3, %%eax	\n"
	"int $0x80	\n"

	"movl %0, %%esi	\n"
	"addl %%esi, %1	\n"
	"movl $0x4, %%eax	\n"
	"int $0x80	\n"
	:
	:"m"(a), "m"(b)
	:"memory"
	);
	return 0;
}
