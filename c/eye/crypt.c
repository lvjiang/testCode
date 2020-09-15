#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		fprintf(stderr, "%s salt key\n", argv[0]);
		return -1;
	}

	char *encrypted = NULL;
	encrypted = crypt(argv[2], argv[1]);
	if(NULL == encrypted) {
		fprintf(stderr, "crypt error:%s\n", strerror(errno));
	}

	printf("%s encrypted: %s\n", argv[2], encrypted);

	return 0;
}
