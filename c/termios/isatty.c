#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *name;
	if (isatty(STDIN_FILENO)) {
		name = ttyname(STDIN_FILENO);
		if (name == NULL) {
			name = "undefined";
		}
	} else {
		name = "not a tty";	
	}
	printf("fd 0:%s\n", name);

	if (isatty(STDOUT_FILENO)) {
		name = ttyname(STDOUT_FILENO);
		if (name == NULL) {
			name = "undefined";
		}
	} else {
		name = "not a tty";	
	}
	printf("fd 1:%s\n", name);

	if (isatty(STDERR_FILENO)) {
		name = ttyname(STDERR_FILENO);
		if (name == NULL) {
			name = "undefined";
		}
	} else {
		name = "not a tty";	
	}
	printf("fd 2:%s\n", name);

	return 0;
}
