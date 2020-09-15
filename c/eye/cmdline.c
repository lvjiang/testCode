#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char path[256];
	int i = 0;
	FILE *fp = NULL;
	char c;

	if(2 != argc) {
		printf("please select a cmdline file\n");
		return -1;
	}

	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "%s", argv[1]);

	fp = fopen(path, "r");
	if(NULL == fp) {
		printf("open %s file error\n", path);
		return -1;
	}

	while(!feof(fp)) {

		c = fgetc(fp);
		printf("%x ", c);
	}

	fclose(fp);
	fp = NULL;
	return 0;
}
