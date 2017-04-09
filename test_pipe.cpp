/**
 * @file test_pipe.cpp
 * @brief
 * @version 1.0
 * @date 07/21/2016 11:00:19 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <unistd.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
    const char shit[512] = "shit";
    int pipefd[2];
	ssize_t size;

    if (pipe2(pipefd, O_NONBLOCK | O_CLOEXEC)) {
        cout << "pipe error" << endl;
        return -1;
    }

    for (int i = 0; ;) {
        size = write(pipefd[1], shit, sizeof(shit));
        if (size != sizeof(shit)) {
            cout << "write up to " << i << endl;
            usleep(1000000);
            continue;
        }
        ++i;
    }

    return 0;
}

