#include<stdio.h>

int main(void)
{
	int a[7] = {0,1,2,3,4,5,6};
	int i = 0;
	for (i = 0; i < sizeof(a)/sizeof(int); i++) {
		printf("%d\n", a[i]);
	}

	int *p = a;
	printf("p = %d\n", *(p+2));
	return 0;
}
