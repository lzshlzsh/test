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

    pid = fork();
    if (!pid) {
      signal(SIGINT, SIG_IGN);
      signal(SIGTERM, SIG_IGN);
      sleep(1);
      while (1) { sleep(1); }
    }

    for (; ;) {
      pid = waitpid(-1, &status, WNOHANG);
      if (pid > 0) {
        cout << pid << endl;
        if (WIFSIGNALED(status)) {
          cout << "terminated by signal " << WTERMSIG(status) << endl;
        }
        break;
      }
      usleep(10000);
    }

    return 0;
}

