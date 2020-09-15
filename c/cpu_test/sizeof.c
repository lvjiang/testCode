#include<stdio.h>

int main(int argv, char **argc)
{
	int *p;
	printf("sizeof(char)=%lu\n", sizeof(char));
	printf("sizeof(short)=%lu\n", sizeof(short));
	printf("sizeof(short int)=%lu\n", sizeof(short int));
	printf("sizeof(int)=%lu\n", sizeof(int));
	printf("sizeof(long)=%lu\n", sizeof(long));
	printf("sizeof(long int)=%lu\n", sizeof(long int));
	printf("sizeof(long long)=%lu\n", sizeof(long long));
	printf("sizeof(long long int)=%lu\n", sizeof(long long int));
	printf("sizeof(p)=%lu\n", sizeof(p));
	printf("sizeof(float)=%lu\n", sizeof(float));
	printf("sizeof(double)=%lu\n", sizeof(double));

	return 0;
}
