#include <stdio.h>
#define LINE "lvsj:x:1000:1000::/home/lvsj:/bin/bash"

int main(int argc, char *argv[])
{
    int numb = -1;
	char username[32];
	char info[32];
	char home[64];
	char shell[64];
	int uid,gid;
	
	numb = sscanf(LINE,"%[^:]:%*[^:]:%d:%d:%[^:]:%[^:]:%s", username,&uid,&gid,info,home,shell);
	printf("numb=%d\n", numb);
	printf("username=%s, uid=%d, gid=%d, info=%s, home=%s, shell=%s \n",username, uid, gid, info, home, shell);
}
