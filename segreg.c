int main()
{
	asm volatile(
	"movl %gs:0x10, %eax\n"
	);
	return 0;
}
