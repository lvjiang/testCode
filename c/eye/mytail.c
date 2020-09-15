#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

unsigned int old_size = 0;

int main(int argc, char** argv) {
	char buffer[1024];
	char line[1024];
	int ch;
	long curFilePointer;
   	FILE *fp;
	int fd;
	int wd;
	struct stat s;
	if(argc!=2){
		printf("usage: tail file-path.\n");
		return EXIT_FAILURE;
	}
	fp=fopen(argv[1],"r");
	if(fp<0){
		printf("can't open %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	fseek(fp, 0, SEEK_END);
	old_size = ftell(fp);

	fd = inotify_init();
	if (fd < 0) {
		printf("Fail to initialize inotify.\n");
		return EXIT_FAILURE;
	}
	wd = inotify_add_watch(fd, argv[1], IN_MODIFY);
	if (wd < 0) {
		printf("Can't add watch for %s.\n", argv[1]);
		return EXIT_FAILURE;
	}

	while(1){
		if(!stat(argv[1], &s)) {
			printf("old_size=%u, st_size=%u\n", old_size, s.st_size);
			if(old_size > s.st_size) {
				rewind(fp);
				old_size = 0;
				printf("-------rewind-------\n");
			} else {
				old_size = s.st_size;
				printf("------------------------\n");

			}
			while ((fgets(line, sizeof(line), fp))) {
				printf("lv:%s", line);
			}
		} else {
			printf("stat error!!!\n");
		}
		read(fd, buffer, 1024);
	}

	return EXIT_SUCCESS;
}
