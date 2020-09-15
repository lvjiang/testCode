#include <stdio.h>
//#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
//#include <unistd.h>
#define _GNU_SOURCE
#include <crypt.h>

int main(int argc, const char *argv[])
{
	char *passwd;
	char key[] = "123456";
	passwd = crypt(argv[1], argv[2]);
	printf("password: %s\n", passwd);
	return 0;
}
