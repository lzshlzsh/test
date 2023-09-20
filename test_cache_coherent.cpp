//
// Created by lzs on 11/2/20.
//

#include <pthread.h>

static int x __attribute__((aligned(64)));
static int y __attribute__((aligned(64)));

static void *thread_func1(void *params) {
    for (int i = 0; i < 1000000000; i++) {
        x++;
    }
    return nullptr;
}

static void *thread_func2(void *params) {
    volatile int c;
    for (int i = 0; i < 1000000000; i++) {
        c = x;
    }
    return nullptr;
}

int main(int argc, char **argv) {
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, thread_func1, nullptr);
    pthread_create(&t1, nullptr, thread_func2, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    return 0;
}
