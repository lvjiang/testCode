#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int ret,i;
	char c[30];
	char a[4];
	char d[78];
	char b[8];
	

	a[0] = 'l';
	a[1] = 'v';
	a[2] = 'v';
	a[3] = 's';
//	a[2] = 'g';

	b[0] = 'l';
	b[1] = 'v';
	b[2] = 'v';
	b[3] = 's';

	
	printf("ret=%d,i=%d\n", ret, i);
	for (i=0; i < 16; i++) {
		printf("a[%d]=%c ", i, a[i]);
	}
	printf("\n");
	for (i=0; i < 16; i++) {
		printf("b[%d]=%c ", i, b[i]);
	}
	printf("\n");

	ret = strncmp(a, b, 8);
//	ret = strcmp(a, b);

	printf("a_l=%ld, b_l=%ld\n", strlen(a), strlen(b));
	printf("ret=%d\n", ret);
}
