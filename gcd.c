// һ�������Լ���ĳ��� 
// ���������һ������������޸��ñ�����󣬲������ó���������� 

#include <stdio.h> 

int gcd(int n, int m) 
{ 
    while (n != m) 
    { 
        if (n > m) 
            n -= m;
        else 
            m -= n; 
    } 

    return n; 
} 

int main(void) 
{ 
    int n = 71825; 
    int m = 60455; 
    int x = gcd(n, m); 
    printf("%d\n", x); 
	return 0;
} 
