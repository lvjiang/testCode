#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t t;
	struct tm tm;
	char buf[255];

	memset(&tm, 0, sizeof(struct tm));
	strptime("2001-11-2 18:31:01", "%Y-%m-%d %H:%M:%S", &tm);
	strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
	puts(buf);
	
	//tm.tm_min = tm.tm_min - 40;
	tm.tm_mon = 40;
	t = mktime(&tm);
	printf("t=%ld\n", t);
	printf("t=%s\n", ctime(&t));

	while(1) {
		t = time(NULL);

		printf("t=%s\n", ctime(&t));
		sleep(10);
	}
}
