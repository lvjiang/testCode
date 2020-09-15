#include<stdio.h> 
#include<string.h>
#define N 5 
int main(int agrc,char *argv[]) 
{     
	int count = 0;
	char buf[N];
	FILE *fp;   

	if (agrc < 2) {
		printf("user: %s <filename>",argv[0]);
	}     

	if ((fp = fopen(argv[1],"r")) == NULL) {   
		perror("fail to open");
		return -1;
	}

	while (fgets(buf,N,fp)) {
		if(buf[strlen(buf) - 1]=='\n')
			count++;
	}

	printf("Total line :%d\n",count);

	return 0; 
}
