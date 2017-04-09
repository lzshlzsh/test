/*
 * =====================================================================================
 *
 *       Filename:  shmget.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2014 03:01:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>

using namespace std;

const int DEFAULT_KEY = 24555;
const int DEFAULT_SIZE = 12000;

int usage(const char *file)
{
	std::cout << file << " key size" << std::endl;
	std::cout << "default: key " << DEFAULT_KEY << ", size " << DEFAULT_SIZE << std::endl;
	return 0;
}

int my_atoi(const char *str) {
    return (str[0] == '0') ? 
        ((str[1] == 'x' || str[1] == 'X') ? strtol(str, NULL, 16) : strtol(str, NULL, 8)) :
        atoi(str);
}

int main(int argc, char **argv)
{
	int key = DEFAULT_KEY;
	size_t size = DEFAULT_SIZE;
	int shm_id;

	if ( 3 != argc) {
		usage(argv[0]);
	}
	if (argc >= 2) {
        key = my_atoi(argv[1]);
	}
	if (argc >= 3) {
        size = my_atoi(argv[2]);
	}

	std::cout << "key: " << key << ", size: " << size << std::endl;

	if (-1 == (shm_id = shmget(key, size, 0666))) {
		if (-1 == (shm_id = shmget(key, size, 0666 | IPC_CREAT))) {
			std::cout << "shmget failed: " << strerror(errno) << std::endl;
			exit(1);
		}
	}
	if ((void *)-1 == shmat(shm_id, NULL, 0)) {
		std::cout << "shmat failed: " << strerror(errno) << std::endl;
		exit(1);
	}

	return 0;
}
