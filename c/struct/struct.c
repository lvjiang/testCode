#include <stdio.h>

struct nullType{
	int arry[0];
};

int main(int argc, char *argv[])
{
	int len;
	len = sizeof(struct nullType);
	struct nullType test;
	printf("%d\n", len);
	printf("sizeof(test)=%lu\n", sizeof(test));
}
