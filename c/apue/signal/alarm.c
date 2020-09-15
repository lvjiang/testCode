#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	alarm(5);
	while(1) {
		printf("haha...\n");
		sleep(1);
	}
	printf("exit\n");
	return 0;
}
