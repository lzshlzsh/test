/**
 *	Created Time: 2009-09-10 17:26:56
 *	Last Modified: 2009-09-10 17:26:56
 *	File Name: dynamic_cast.cpp
 *	Description: 
 */
#include <iostream>

class B
{
public:
	int m_iNum;
	virtual void foo(){};
};
class D : public B
{
public:
	char *m_szName[100];
};

class E : public B
{
public:
	char *m_szName[100];
};
void func(B *pb)
{
	D *pd1 = static_cast<D *>(pb);
	D *pd2 = dynamic_cast<D *>(pb);
	D *pd = new D;
	E *pd3;// = static_cast<E *>(pd);
	E *pd4 = dynamic_cast<E *>(pd);

	std::cout << "pd1 : " << pd1 << "   pd2 : " << pd2 << std::endl;
	std::cout << "pd3 : " << pd3 << "   pd4 : " << pd4 << std::endl;
	pd1->m_szName[1] = const_cast<char *>("xxxx");
	std::cout << pd1->m_szName[1] << std::endl;
	delete pd;
}

int main()
{
	B b;
	func(&b);
	return 0;
}
