#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned long long a;
	unsigned long long b;
	unsigned long long c;

	a = 4294967296;
	b = 1024;

	c = a * b * b;

	printf("c=%llu\n", c);
	return 0;
}
