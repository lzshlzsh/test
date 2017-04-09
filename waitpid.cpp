/**
 * @file waitpid.cpp
 * @brief
 * @version 1.0
 * @date 11/24/2015 05:30:55 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    pid_t pid;
    int status;
    vector<pid_t> pid_all;

    for (int i = 0; i < 5; ++i) {
        pid = fork();
        if (!pid) {
            sleep(1);
//            exit(0);
            while (1) { sleep(1); }
        } else {
            pid_all.push_back(pid);
        }
    }


    for (unsigned int i = 0; ; i++) {
        pid = waitpid(-1, &status, WNOHANG);
        if (pid > 0) {
            cout << pid << endl;
        } else {
            sleep(1);
            if (!pid_all.empty()) {
                kill(pid_all.back(), SIGKILL);
                pid_all.pop_back();
            }
        }
    }

    return 0;
}

