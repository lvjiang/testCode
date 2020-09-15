#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char buf[] = "mac=99:00:00:00:02:11&pid=1006907362&sign=f51ed3cac72c7e845cb08e9c3b83f500&tt=1551238138";
	char mac[32];
	char pid[32];
	char sign[64];
	time_t timestamp;

	sscanf(buf, "mac=%*[^&]&pid=%*[^&]&sign=%*[^&]&tt=%ld", &timestamp);

	//printf("mac=%s,pid=%s,sign=%s,tt=%ld\n", mac, pid, sign, timestamp);
	printf("tt=%ld\n", timestamp);

}
