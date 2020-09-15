#include<stdio.h>
#include<string.h>

int main()
{
	char line[128];
	long int user,nice,sys,idle,wait,hirq,sirq;
	long  int sum = 0;
	float u, n , s , w,  i;
	FILE *fp = NULL;
	memset(line, 0, sizeof(line));
		
	fp = fopen("/proc/stat", "r");
	if(NULL == fp) {
		printf("file  open failed!\n");
		return -1;
	}

	fgets(line, 128, fp);

	if(7 != sscanf(line, "cpu %lu %lu %lu %lu %lu %lu %lu",
						&user,&nice,&sys,&idle,&wait,&hirq,&sirq)) {
			return -1;
	}

	printf("cpu %lu %lu %lu %lu %lu %lu %lu\n",
			user, nice, sys, idle, wait, hirq, sirq);
	
	sum = user + nice + sys + idle + wait + hirq + sirq;
	printf("sum = %ld\n",sum);

	u = 100.0 * user/sum;
	n = 100.0 * nice/sum;
	s = 100.0 * sys/sum;
	w = 100.0 * wait/sum;
	i = 100.0 * idle/sum;
	
	printf("u=%f,n=%f,s=%f,w=%f,i=%f\n", u, n , s, w, i);

	fclose(fp);
	return 0;
}
