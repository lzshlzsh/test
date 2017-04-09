/**
 * @file enum.cpp
 * @brief
 * @version 1.0
 * @date 11/02/2015 05:35:47 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <iostream>

using namespace std;

enum {
    START = 1,
    A = START,
    B,
    C,
    NUM = C - START + 1,
};

int main() {
    cout << NUM << endl;
    return 0;
}
