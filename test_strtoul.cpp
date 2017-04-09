/*
 * =====================================================================================
 *
 *       Filename:  test_strtoul.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/2013 03:52:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <iostream>

int main()
{
    const char buf[] = "76c\r\naaa";
    char *end;
    unsigned long int val;

    val = std::strtoul(buf, &end, 16);
    std::cout << buf << std::endl;
    std::cout << val << '\t' << end - buf << '\t' << end << std::endl;

    return 0;
}
