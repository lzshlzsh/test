/**
 * @file for.cpp
 * @brief
 * @version 1.0
 * @date 04/22/2016 11:21:38 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

int main()
{
    int k = 9, l = 3;
    for (int i = 0; i < 1000; ++i) {
        k = l * 9;
        l += k;
    }
    return 0;
}

