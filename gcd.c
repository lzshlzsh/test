// 一个求最大公约数的程序 
// 这个程序含有一个编译错误，请修复该编译错误，并给出该程序的输出结果 

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
