#include<stdio.h>
struct test {
	int a;
	int b;
	int p[];
};

int main()
{
	printf("len=%d\n",sizeof(struct test));
}
