#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t t;
	while(1) {
		t = time(NULL);
		printf("t=%ld\n",t);
		sleep(10);
	}
}
