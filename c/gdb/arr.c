#include <stdio.h>
int main()
{
	int i,a[5];
	printf("i:%p\n",&i);
	printf("a:%p\n",a);
	for(i=0; i<=5;i++) {
		a[i] = 0;
		printf("a[%d]=%d\n",i, a[i]);
	}
	return 0;
}
