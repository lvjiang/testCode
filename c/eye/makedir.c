#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int makeDir(const char* path)  
{  
	int beginCmpPath;  
	int endCmpPath;  
	int fullPathLen;
	int i;
	int pathLen = strlen(path);  
	char currentPath[128] = {0};  
	char fullPath[128] = {0};  

	printf("path = %s\n", path);  
	/* Relative Path */
	if ('/' != path[0]) {     
		/* get current path */
		getcwd(currentPath, sizeof(currentPath));  
		strcat(currentPath, "/");  
		printf("currentPath = %s\n", currentPath);  
		beginCmpPath = strlen(currentPath);  
		strcat(currentPath, path);  
		if(path[pathLen] != '/')  
		{  
			strcat(currentPath, "/");  
		}  
		endCmpPath = strlen(currentPath);            
	}  
	else  
	{  
		/*Absolute Path*/
		int pathLen = strlen(path);  
		strcpy(currentPath, path);  
		if(path[pathLen] != '/')  
		{  
			strcat(currentPath, "/");  
		}  
		beginCmpPath = 1;  
		endCmpPath = strlen(currentPath);  
	}  
	/* creat path */  
	for(i = beginCmpPath; i < endCmpPath ; i++ )  
	{  
		if('/' == currentPath[i])  
		{  
			currentPath[i] = '\0';  
			if(access(currentPath, NULL) != 0)  
			{  
				if(mkdir(currentPath, 0755) == -1)  
				{  
					printf("currentPath = %s\n", currentPath);  
					perror("mkdir error %s\n");  
					return -1;  
				}  
			}  
			currentPath[i] = '/';  
		}  
	}  
	return 0;  
} 

int main(int argc, char *argv[])
{
	makeDir(argv[1]);
	printf("argv[0]=%s\n",argv[0]);
	printf("argv[1]=%s\n",argv[1]);
	return 0;	
}
