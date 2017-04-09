/**
 * @file convertion_operator.cpp
 * @brief
 * @version 1.0
 * @date 11/07/2015 11:34:06 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <iostream>

using namespace std;

struct To {
    To() {}
    To(const struct From&) {
        cout << __LINE__ << endl;
    } // converting constructor
};
 
struct From {
    operator To() {
        cout << __LINE__ << endl;
        return To();
    } // conversion function
};
 
int main()
{
    From f;
    To t1(f); // direct-initialization: calls the constructor
// (note, if converting constructor is not available, implicit copy constructor
//  will be selected, and conversion function will be called to prepare its argument)
    To t2 = f; // copy-initialization: ambiguous
// (note, if conversion function is from a non-const type, e.g.
//  From::operator To();, it will be selected instead of the ctor in this case)
    To t22 = From();
    To t3 = static_cast<To>(f); // direct-initialization: calls the constructor
    const To& r = f; // reference-initialization: ambiguous
    return 0;
}

