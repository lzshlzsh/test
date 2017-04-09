/**
 * @file macro-cpp2.cpp
 * @brief
 * @version 1.0
 * @date 06/16/2016 11:40:25 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

#define A(_a_) "ads"
#define B "cde"

int main() {
    cout << A(0) << endl;
    return 0;
}

