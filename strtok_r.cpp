/**
 * @file strtok_r.cpp
 * @brief
 * @version 1.0
 * @date 11/16/2015 03:36:37 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str = "a,b,c,,d";
    char *saved_ptr;
    char *start = const_cast<char *>(str.data());
    char *token;
   
    cout << "origin str: " << str << endl;

    while ((token = strtok_r(start, ",", &saved_ptr))) {
        cout << token << endl;
        start = NULL;
    }

    cout << "after strtok_r: " << str << endl;

    return 0;
}

