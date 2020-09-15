#include <stdio.h>
#include <pwd.h>

int main(int argc, char argv[])
{
	struct passwd *pd = NULL;
	int line = 0;
	endpwent();
	while(pd = getpwent()) {
		line++;
		printf("%d  %s:%s:%d:%d:%s:%s:%s\n",line, pd->pw_name, pd->pw_passwd, pd->pw_uid, pd->pw_gid, pd->pw_gecos, pd->pw_dir, pd->pw_shell);
	}
printf("1111111111111111111\n");	
//	setpwent();
	endpwent();
	line = 0;
	while(pd = getpwent()) {
		line++;
		printf("%d  %s:%s:%d:%d:%s:%s:%s\n",line, pd->pw_name, pd->pw_passwd, pd->pw_uid, pd->pw_gid, pd->pw_gecos, pd->pw_dir, pd->pw_shell);
	}
	return 0;
}
