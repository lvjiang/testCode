#include <stdio.h>

int main(int argc, char **argv)
{
	while (*argv) {
		printf("%s\t", *argv);

		argv = argv + 1;
	}

	printf("\n");

}
