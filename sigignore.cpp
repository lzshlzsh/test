#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

#define ERROR(args...) do { \
    printf(args); \
    printf("\n"); \
} while (0)

static void sigint_handler(int signum)
{
    std::cout << "signal: " << signum << std::endl;
    exit(0);
}

static int init_signal()
{
    struct sigaction sigact;

    sigact.sa_handler = SIG_IGN;
    sigfillset(&sigact.sa_mask);
    sigact.sa_flags = 0;

    for (int i = 1; i < _NSIG; i++) {
        if (SIGKILL != i && SIGSTOP != i && SIGINT != i
            && SIGTERM != i && 32 != i && 33 != i) {
            if (sigaction(i, &sigact, NULL) < 0) {
                perror("sigaction");
                ERROR("sigaction for %d failed", i);
            }
        }
    }

    sigact.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        perror("sigaction");
        ERROR("sigaction for SIGINT failed");
        return -1;
    }
    if (sigaction(SIGTERM, &sigact, NULL) < 0) {
        perror("sigaction");
        ERROR("sigaction for SIGTERM failed");
        return -1;
    }
    
    return 0;
}

int main()
{
    if (init_signal()) {
        std::cout << "init_signal failed" << std::endl;
        return -1;
    }
    while (1) {
        sleep(5);
    }
    return 0;
}
