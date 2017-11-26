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

class A {
public:
  int foo() {
    std::cout << "foo" << std::endl;
    return 0;
  }
};

class Const {
  A *a;
public:
  Const(): a(new A()) {}

  int const1() const {
    return 10;
  }
  int const2() const {
    return a->foo();
  }
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
  
  const Const con;

  cout << con.const1() << endl;
  cout << con.const2() << endl;

	return 0;

}
