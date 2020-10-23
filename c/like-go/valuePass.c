#include <stdio.h>

void func(int *x);

int main() 
{
	int a = 1;
	int *p = &a;
	printf("&a=%p\n", &a);
	printf(" p=%p\n", p);
	printf("&p=%p\n", &p);
	func(&a);
	return 0;
}


void func(int *x)
{
	printf(" x=%p\n", x);
	printf("&x=%p\n", &x);
}
