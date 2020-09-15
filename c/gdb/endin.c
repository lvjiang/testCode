#include <stdio.h>
#include <string.h>

void usebuf(char *buf)
{
	buf[24] = 1;
}

int main()
{
	int buf[8];
	int a[4];
	int b[4];
	printf("buf:%p\n",buf);
	printf("buf[0]:%p\n",&buf[0]);
	printf("buf[1]:%p\n",&buf[1]);
	printf("buf[2]:%p\n",&buf[2]);
	printf("buf[7]:%p\n",&buf[7]);
	printf("buf[8]:%p\n",&buf[8]);
	printf("buf[9]:%p\n",&buf[9]);
	printf("buf[10]:%p\n",&buf[10]);
	printf("buf[11]:%p\n",&buf[11]);
	printf("buf[12]:%p\n",&buf[12]);
	printf("a=%p\n",a);
	printf("a0=%p\n",&a[0]);
	printf("a1=%p\n",&a[1]);
	printf("a=%d\n",a[2]);
	printf("a=%d\n",a[3]);
	printf("b=%p\n",b);
	printf("b0=%p\n",&b[0]);
	printf("b1=%p\n",&b[1]);
	printf("b=%d\n",b[2]);
	printf("b=%d\n",b[3]);
	buf[12] = 12;
	return 0;
}
