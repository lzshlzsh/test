/**
 * @file write.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 05:31:34 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <unistd.h>
#include <dlfcn.h>

#include "libcom.h"

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    COUT << __FUNCTION__ << "shit write" << std::endl; 
    COUT << __FUNCTION__ << "dlsym(RTLD_DEFAULT, \"write\")"
        << dlsym(RTLD_DEFAULT, "write") << std::endl;
    COUT << __FUNCTION__ << "dlsym(RTLD_NEXT, \"write\")"
        << dlsym(RTLD_NEXT, "write") << std::endl;
    return 0;
}


