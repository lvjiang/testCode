#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
	int (*pStrlenFun)(char * pStr);
	int (*pStrnlenFun)(char *pStr, int len);

	char str[] = {"hello world"};
	int ulLength = 0;

	void *pdlHandle;
	char *pszErr;

	pdlHandle = dlopen("./libstrdl.so", RTLD_LAZY);
	if(!pdlHandle) {
		printf("Failed load library\n");
	}

	pszErr = dlerror();
	if(pszErr != NULL){
		printf("%s\n", pszErr);
		return 0;
	}

	pStrlenFun = dlsym(pdlHandle, "Strlen");
	pszErr = dlerror();
	if(pszErr != NULL){
		printf("%s\n", pszErr);
		return 0;
	}

	pStrnlenFun = dlsym(pdlHandle, "Strnlen");	
	pszErr = dlerror();
	if(pszErr != NULL){
		printf("%s\n", pszErr);
		return 0;
	}

	printf("The string is :%s\n", str);
	ulLength = pStrlenFun(str);
	printf("The string length is :%d(use Strlen)\n", ulLength);

	ulLength = pStrnlenFun(str, 10);
	printf("The string length is :%d(use Strnlen)\n", ulLength);
	
	dlclose(pdlHandle);
	return 0;
}
