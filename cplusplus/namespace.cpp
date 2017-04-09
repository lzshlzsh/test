#include <iostream>

namespace Na
{
	void f();
}

namespace Nb
{
	void f();
}

void Na::f()
{
	std::cout << "Na::f()" << std::endl;
}

void Nb::f()
{
	std::cout << "Nb::f()" << std::endl;
}

int main()
{
	using namespace Na;
	using namespace Nb;
	Na::f();
	Nb::f();
	using Nb::f;
	f();
	return 0;
}
