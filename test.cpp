/**
 * @file test.cpp
 * @brief
 * @version 1.0
 * @date 04/15/2016 02:53:29 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int i = 33;
    double d = 190.234235234523452345;

    cout << std::setprecision(16) << i << "\t" << d << endl;
    cout << i << "\t" << d << endl;

    return 0;
}

