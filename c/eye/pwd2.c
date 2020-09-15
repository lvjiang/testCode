#include <stdio.h>
#include <pwd.h>

int main(int argc, char argv[])
{
	struct passwd *pd = NULL;
	int line = 0;
	endpwent();
	while(pd = getpwent()) {
		if (strstr(pd->pw_shell, "bash")
				|| strstr(pd->pw_shell, "ash")
				|| strstr(pd->pw_shell, "clish")) {
			printf("good good good:");
		}
		if (!strlen(pd->pw_shell)) {
			printf("==good good good:");
		}
		line++;
		printf("%d  %s:%s:%d:%d:%s:%s:%s\n",line, pd->pw_name, pd->pw_passwd, pd->pw_uid, pd->pw_gid, pd->pw_gecos, pd->pw_dir, pd->pw_shell);
	}
	return 0;
}
