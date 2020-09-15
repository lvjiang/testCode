#include <stdio.h>


int main(int argc, char *argv[])
{
	char *ptr = NULL;

	printf("ptr=%p\n", ptr);
	printf("ptr=%x\n", ptr);
	printf("&ptr=%p\n", &ptr);

	ptr = malloc(6);

	printf("ptr=%p\n", ptr);
	printf("ptr=%x\n", ptr);
	printf("&ptr=%p\n", &ptr);

	return 0;
}
