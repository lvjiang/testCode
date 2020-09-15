#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("_POSIX_ARG_MAX=%d\n", _POSIX_ARG_MAX);

	printf("_SC_ARG_MAX=%ld\n", sysconf(_SC_ARG_MAX));
#ifdef _POSIX_NAME_MAX
	printf("_PC_NAME_MAX=%ld\n", pathconf("/", _PC_NAME_MAX));
#endif
	printf("_PC_PATH_MAX=%ld\n", pathconf("/", _PC_PATH_MAX));
	printf("_PC_PATH_MAX=%ld\n", pathconf("./", _PC_PATH_MAX));
	printf("Size of a page in bytes:%ld\n",sysconf(_SC_PAGESIZE));
	printf("Max length of a  hostname:%ld\n",sysconf(_SC_HOST_NAME_MAX));
	printf("The maximum number of files that a process can have open at any time.:%ld\n",sysconf(_SC_OPEN_MAX));
	printf("The  number  of  clock  ticks  per  second.:%ld\n",sysconf(_SC_CLK_TCK)); 
	printf("The number of processors currently online .:%ld\n",sysconf(_SC_NPROCESSORS_ONLN)); 
	printf("The number of processors configured..:%ld\n",sysconf(_SC_NPROCESSORS_CONF));

	printf("_SC_SYMLOOP_MAX=%ld\n", sysconf(_SC_SYMLOOP_MAX));

}
