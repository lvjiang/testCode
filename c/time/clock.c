#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct timespec res;
	struct timespec ts;
	clock_getres(CLOCK_MONOTONIC, &res);
	printf("res_sec=%ld, res_nsec=%ld\n", res.tv_sec, res.tv_nsec);
	while(1) {
		clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
		printf("ts_sec=%ld, ts_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);
		sleep(10);
	}
}
