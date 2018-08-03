#include <iostream>

using namespace std;

bool b = true;

template <int i>
int foo() {
  return 0;
}

template<>
int foo<1>() {
  return 10;
}

int main()
{
  int a = 1;
  a = !a;
  cout << a << endl; 
  a = !a;
  cout << a << endl; 
  a = !a;
  cout << a << endl; 

  cout << foo<9>() << endl;
  cout << foo<1>() << endl;
  return 0;
}
