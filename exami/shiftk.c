#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int gcd(int a, int b)
{
	a = a ? a : -a;
	b = b ? b : -b;
	if (a < b){
		//swap
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
	if (0 == b)
		return a;
	return gcd(b, a % b);
}

static void shiftk(int A[], int n, int k)
{
	int d, i, j;
	int x, t;
	//TODO:
	if (!k)
		return;
	d = gcd(n, k);
	printf("gcd(%d, %d) = %d\n", n, k, d);
	for (i = 0; i < d; i++){
		x = A[i];
		t = i;
		for (j = 1; j < n / d; j++){
			A[t] = A[(t + k) % n];
			t = (t + k) % n;
		}
		A[t] = x;
	}
}


int main()
{
	unsigned int state;
	int n, k;

	srand((unsigned int)time(NULL));
	
	n = rand_r(&state) % 100 + 1;
	k = rand_r(&state) % 100 + 1;

	if (n < k){
		n = n ^ k;
		k = n ^ k;
		n = n ^ k;
	}

	int A[n];
	int i;
	for (i = 0; i < n; i++)
		A[i] = i;

	shiftk(A, n, k);

	printf("%d shift %d: \n", n, k);
	for (i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");
		
	return 0;
}
