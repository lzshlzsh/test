/**
 * @file do_write.cpp
 * @brief
 * @version 1.0
 * @date 06/01/2016 09:00:51 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <unistd.h>

int do_write() {
    const char buf[] = "shit write";
    write(1, buf, sizeof(buf));
    return 0;
}

