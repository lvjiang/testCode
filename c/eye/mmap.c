#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define N 8

int main(int argc, char *argv[])
{
	char line[128];
	char buf[] = "---hahahahahahhah---";
	int fd;
	int offset, i;
	char *mapped;

	fd = open(argv[1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	if (fd < 0) {
		perror("open faild");
	} else {
		write(fd,"s", 2);
		lseek(fd, 128*8 - 2, SEEK_SET);
		write(fd, "e", 2);
	}
	
/*	memset(line, 0, 128);
	for (i = 0; i < 8; i++) {
		write(fd, line, 128);
	}
*/
	printf("11111111111111\n");
	mapped = mmap(NULL, sizeof(line) * N, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (NULL == mapped) {
		perror("mmap");
	}

	printf("2222222222222222\n");

	for (i = 0; i < N; i++) {
		offset = sizeof(line) * i;
		memcpy(mapped+offset, buf, sizeof(buf));
	}		

}
