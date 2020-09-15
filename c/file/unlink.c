#include <stdio.h>
#include <unistd.h>

int main(int argc, char **args)
{
	unlink(args[0]);
	printf("Delete self OK.\n");
	while(1);
}
