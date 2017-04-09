
void foo()
{
	static int i = 1;
	i++;
}

int main()
{
	foo();
	return 0;
}
