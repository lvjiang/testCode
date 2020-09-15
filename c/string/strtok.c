#include<stdio.h>
#include<string.h>
int main(void)
{
	int i = 0;
	char buf[]="hello@boy@this@is@heima";
	char*temp = strtok(buf,"@");
	while(temp)
	{
		printf("i=%d,%s\n",i++, temp);
		temp = strtok(NULL,"@");
	}
	printf("buf=%s\n",buf);
	return 0;
}
