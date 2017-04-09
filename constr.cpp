#include <iostream>
#include <string>

using namespace std;

class test

{

	public:

		test(){}

		test(int a){}

		void fun(){}

	protected:

	private:

};

int main()

{

	test a(10);

	a.fun();

//	test b();//Ops: declare of a func 
	test b;

	b.fun();  //这里编译错误warning C4520: 'test' :

	//multiple default constru
	//把上面的语句改成test b;就可以了

	return 0;

}
