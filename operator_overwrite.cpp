#include <iostream>

using namespace std;

class A 
{
    int a;
public:
    size_t operator()(/*const A &a*/)
    {
        return sizeof(A);
    }

};

int main()
{
    A a;

    cout << a() << endl;
    return 0;
}
