/**
 * @file test_memcpy.cpp
 * @brief
 * @version 1.0
 * @date 07/21/2016 11:19:12 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <string.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main() { 
    const int MV_SZ = 64 << 10;
    const int SHIFT_SZ = 258;
    const int BUF_SZ = MV_SZ + SHIFT_SZ;

    char txt[MV_SZ]; 
    char buf[BUF_SZ];

    for (unsigned int i = 0; i < sizeof(txt); ++i) {
        txt[i] = i;
    }

    for (; ;) {
        memcpy(buf + SHIFT_SZ, txt, MV_SZ);
        memcpy(buf, buf + SHIFT_SZ, MV_SZ);

        if (memcmp(txt, buf, MV_SZ)) {
            cout << "memcpy fail" << endl;
            break;
        } else {
            cout << "memcpy success" << endl;
            usleep(10000);
        }
    }
    return 0;
}

