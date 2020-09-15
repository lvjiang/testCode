#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	struct timeval tv;
	struct timeval *tt;

	tv.tv_sec = 100;
	tv.tv_usec = 0;
	if(adjtime(&tv, tt)) {
		perror("adjtime");		
	}
	if (tt) {
		printf("tt.tv_sec=%ld, tt.tv_usec=%ld\n", tt->tv_sec, tt->tv_usec);
	}
}
