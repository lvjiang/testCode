#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int
main(int argc, char *argv[])
{
	printf("fd 0: %s\n", isatty(0) ? "tty" : "not a tty");
	printf("fd 1: %s\n", isatty(1) ? "tty" : "not a tty");
	printf("fd 2: %s\n", isatty(2) ? "tty" : "not a tty");

	printf("fd 0: ttyname %s\n", ttyname(0));
	printf("fd 1: ttyname %s\n", ttyname(1));
	printf("fd 2: ttyname %s\n", ttyname(2));

	printf("ctermid: %s\n", ctermid(NULL));

	return 0;
}
