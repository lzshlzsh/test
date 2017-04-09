/**
 * @file strlen.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 08:31:32 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include "libcom.h"

size_t strlen(const char *s) {
    COUT << s << std::endl;
    COUT << __FUNCTION__ << "dlsym(RTLD_DEFAULT, \"strlen\")"
        << dlsym(RTLD_DEFAULT, "strlen") << std::endl;
    COUT << __FUNCTION__ << "dlsym(RTLD_NEXT, \"strlen\")"
        << dlsym(RTLD_NEXT, "strlen") << std::endl;
    return 0;
}

