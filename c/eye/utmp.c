#include <stdio.h>
#include <utmp.h>
#include <string.h>
#include <time.h>

#define FILE_PATH "/var/run/utmp"

void show_info(struct utmp *utmpfp)
{
	time_t timelong = utmpfp->ut_time;	
	struct tm *localnow = localtime(&timelong);
	if (utmpfp->ut_type == INIT_PROCESS) {
		printf ("-------------INIT_PROCESS-----------\n");
	}

	if (utmpfp->ut_type == LOGIN_PROCESS) {
		printf ("--------------LOGIN_PROCESS-----------\n");
	}

	if (utmpfp->ut_type == USER_PROCESS) {
		printf ("-----------USER_PROCESS--------------\n");
	}

	if (utmpfp->ut_type == DEAD_PROCESS) {
		printf ("-------------DEAD_PROCESS------------\n");
	}

	printf("ut_name=%8s\t", utmpfp->ut_name);
	printf("ut_line=%12s\t", utmpfp->ut_line);
	printf("time=%d-%d-%d %d:%d\t", localnow->tm_year+1900, localnow->tm_mon+1, localnow->tm_mday, localnow->tm_hour, localnow->tm_min);
	printf("ut_host=%s\t", utmpfp->ut_host);
	printf("remoteip=%X\n", utmpfp->ut_addr_v6[0]);
}

int main(int argc, int **argv)
{
	struct utmp current_record;
	FILE *utmpfd = NULL;
	int reclen = sizeof(current_record);
	
	utmpfd = fopen(FILE_PATH, "r");
	if (NULL == utmpfd) {
		printf("file open error!\n");
		return -1;
	}

	memset(&current_record, 0, reclen);

	while ( fread(&current_record, sizeof(char), reclen, utmpfd) == reclen) {
		show_info(&current_record);
		memset(&current_record, 0, reclen);
	}

}
