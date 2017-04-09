/**
 * @file virtual_base_class.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 11:46:31 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <stdint.h>

#include <iostream>

using namespace std;

class PoweredDevice
{
public:
    char c;
    PoweredDevice(int nPower): c('a')
    {
        cout << "PoweredDevice: " << nPower << endl;
    }
//    virtual void foo() {}
};

class Foo {
    int i;
public:
//    virtual void foo() {}
};
 
class Scanner: virtual public PoweredDevice//, virtual public Foo
{
public:
    int j1;
    Scanner(int nScanner, int nPower)
        : PoweredDevice(nPower)
    {
        cout << "Scanner: " << nScanner << endl;
    }
    virtual void doo() {}
};
 
class Printer: virtual public PoweredDevice, virtual public Foo
{
public:
    int j2;
    Printer(int nPrinter, int nPower)
        : PoweredDevice(nPower)
    {
        cout << "Printer: " << nPrinter << endl;
    }
};

class Goo: virtual public Foo {
    int j3;
};
 
class Copier: public Scanner, public Printer, virtual public Goo
{
public:
    Copier(): PoweredDevice(0), Scanner(0, 0), Printer(0, 0) {}
    Copier(int nScanner, int nPrinter, int nPower)
        : PoweredDevice(nPower), Scanner(nScanner, nPower), Printer(nPrinter, nPower)
    {
    }
};

class Xoo {
    uint64_t k;
};

class DCopier: public Copier {};
class DGoo: virtual public Goo, virtual public Xoo {};

class DGooCopier: public DCopier, public DGoo {};

int main()
{
    Copier cCopier(1, 2, 3);

    cout << "sizeof(PoweredDevice) = " << sizeof(PoweredDevice) << endl;
    cout << "sizeof(Foo) = " << sizeof(Foo) << endl;
    cout << "sizeof(Goo) = " << sizeof(Goo) << endl;
    cout << "sizeof(Scanner) = " << sizeof(Scanner) << endl;
    cout << "sizeof(Printer) = " << sizeof(Printer) << endl;
    cout << "sizeof(Copier) = " << sizeof(Copier) << endl;
    cout << "sizeof(DCopier) = " << sizeof(DCopier) << endl;
    cout << "sizeof(DGoo) = " << sizeof(DGoo) << endl;
    cout << "sizeof(DGooCopier) = " << sizeof(DGooCopier) << endl;

    return 0;
}
