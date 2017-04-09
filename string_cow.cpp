/**
 * @file string_cow.cpp
 * @brief
 * @version 1.0
 * @date 06/27/2016 05:50:29 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <string>

using namespace std;
 
int main()
{
    string str1 = "hello world";
    string str2 = str1;
    string str3;

    str3.assign(str1.data(), str1.length());

    printf ("Sharing the memory:\n");
    printf ("ststr1's address: %p\n", str1.c_str() );
    printf ("ststr2's address: %p\n", str2.c_str() );
    printf ("ststr3's address: %p\n", str3.c_str() );

    str2[1]='w';

    printf ("After Copy-On-Write:\n");
    printf ("ststr1's address: %p\n", str1.c_str() );
    printf ("ststr2's address: %p\n", str2.c_str() );
    printf ("ststr3's address: %p\n", str3.c_str() );

    return 0;
}

