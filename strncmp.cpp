/**
 * @file strncmp.cpp
 * @brief
 * @version 1.0
 * @date 03/30/2016 02:54:08 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <libgen.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <iostream>

using namespace std;

int main() {
    char *path = strdup("/jobs/90048");
    string str = path;
    cout << dirname(path) << endl;
    free(path);

    size_t pos = str.rfind('/');
    if (string::npos == pos) {
        cout << "shit" << endl;
        return -1;
    }
    cout << str.substr(0, pos) << endl;

    return 0;
}

