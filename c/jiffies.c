#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

int main()
{
	unsigned long jiffies = 0;
	unsigned long c =0;
	printf("CLOCKS_PER_SEC=%lu\n", CLOCKS_PER_SEC);
	jiffies = times(NULL);
	printf("%lu\n", jiffies);
	printf("time=%lu\n", time(NULL));
	printf("clock=%lu\n", clock());
	sleep(1);
	printf("clock=%lu\n", clock());
	printf("time=%lu\n", time(NULL));
	jiffies = times(NULL);
	printf("%lu\n", jiffies);
	return 0;
}

