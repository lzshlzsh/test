/**
 * @file para-for-private.cpp
 * @brief
 * @version 1.0
 * @date 09/20/2016 03:03:45 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <omp.h>
#include <unistd.h>

#include <iostream>
#include <vector>

int main() {
    std::vector<int> a{100, 200};

    omp_set_num_threads(1);

#pragma omp parallel for schedule(static) private(a)
   for (int i = 0; i < 20; i++) {
       a.emplace_back(i);
       std::cout << '[' << omp_get_thread_num() << ']';
       for (auto &it: a) {
           std::cout << "," << it;
       }
       std::cout << std::endl;
       sleep(1000);
   } 

    return 0;
}
