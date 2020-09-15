#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	int ret = 0;
	alarm(10);
	sleep(3);
	ret = alarm(5);
	printf("ret = %d \n", ret);
	pause();
	printf("exit\n");
	return 0;
}
