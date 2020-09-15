#include<stdio.h>
#include<string.h>
#include<stdint.h>

struct student {
	char name[16];
	char sex;
	uint8_t age;
};

int main(int argc, char **argv)
{
	struct student a;
	struct student b;
	strncpy(a.name,"lvshuaijiang",16);
	a.sex = 1;
	a.age = 27;
	b = a;
	printf("student %s is a %s %d years old\n",a.name,a.sex?"boy":"girl", a.age);
	printf("student %s is a %s %d years old\n",b.name,b.sex?"boy":"girl", b.age);
	return 0;
}
