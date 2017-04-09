#include <iostream>

using namespace std;

#define SIZE (1 << 15)

int main()
{
	cout << endl;
	for (int i = 0; i < SIZE; i++){
		cout << "\033[?25l\033[1A\033[K" << i << "                       \033[32m" << i * 100 / SIZE <<"%\033[0m" << endl;
	}
}
