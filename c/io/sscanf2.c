#include <stdio.h>
int main()
{
	char out[3];
	sscanf("03.05.15", "%x.%x.%x", &out[0],&out[1], &out[2]);
	printf("%d %d %d\n", out[0], out[1],out[2]);

}
