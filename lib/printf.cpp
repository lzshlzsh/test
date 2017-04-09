/**
 * @file printf.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 04:41:45 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <dlfcn.h>

#include "libcom.h"
int printf(const char *format, ...) {
    COUT << __FUNCTION__ << __FILE__ << ":shit:" << format << std::endl; 
    COUT << __FUNCTION__ << "dlsym(RTLD_DEFAULT, \"printf\")"
        << dlsym(RTLD_DEFAULT, "printf") << std::endl;
    COUT << __FUNCTION__ << "dlsym(RTLD_NEXT, \"printf\")"
        << dlsym(RTLD_NEXT, "printf") << std::endl;
    return 0;
}
