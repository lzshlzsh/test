/**
 * @file do_while.cpp
 * @brief
 * @version 1.0
 * @date 01/06/2016 10:40:05 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

int main() {
    int i = 0;
    do {
        cout << ++i << endl;
        continue;
    } while (0);
}

