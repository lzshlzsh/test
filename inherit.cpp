#include <iostream>

using namespace std;

class Super {
    int a;
    int b;
    int geta() const { return a;}
public:
    void seta(int aa) { a = aa;}
    Super(): a(1), b(2) {}
    virtual void vfunc() { cout << __LINE__ << endl; }
};

class SubClass: virtual public Super {
    int a;
    int b;
public:
    SubClass(): a(101), b(102) {}
    int geta() const { return a;}

private:
    virtual void vfunc() { Super::vfunc(); cout << __LINE__ << endl; }
};

int main(int argc, char **argv) {
    SubClass s;

    cout << sizeof(s) << std::endl;
    cout << s.geta() << std::endl;
    s.seta(201);
    cout << s.geta() << std::endl;

    cout << "----" << endl;
    Super &super = s;
    super.vfunc();

    return 0;
}
