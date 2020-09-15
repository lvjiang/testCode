#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	float a = 0.5;
	int b;
	memcpy(&b, &a, 4);

	printf("b=%x\n", b);
	return 0;
}
