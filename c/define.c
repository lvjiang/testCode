#include <stdio.h>

#define STR(a) #a
#define TT test1_
#define __TEST_PRINT(tt) (tt##print)
#define _TEST_PRINT(tt) __TEST_PRINT(tt)
#define TEST_PRINT _TEST_PRINT(TT)

void test1_print(const char *string)
{
	printf("test1:%s\n", string);
}
void test2_print(const char *string)
{
	printf("test2:%s\n", string);
}

int main(int argc, char *argv[]) {
	int biubiu = 3;
	printf("==%s==\n", STR(biubiu));

	TEST_PRINT("hello,world!");
	return 0;
}



