#include <iostream>

using namespace std;

class C
{
    int i_;
public:    
    C(int i): i_(i) {}
    int get() {return i_;}
};

template <typename T>
void foo(int i)
{
    T t(i);
    cout << t.get() << endl;
}

int main()
{
    void (*f)(int) = foo<C>;

    f(9);

    return 0;
}
