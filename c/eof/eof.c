#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
       	int i = 0;
	unsigned char ch = 0;
	FILE *fp = NULL;
	fp = fopen(argv[1],"r");
	if (NULL == fp) {
		perror("fopen error");
		exit(-1);
	}

	do {
		ch = fgetc(fp);
		printf("%c,%d\n",ch,ch);
	} while(!feof(fp));
}
