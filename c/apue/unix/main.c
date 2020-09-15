#include <fcntl.h>

#define BUFFSIZE 8192

int
main(int argc, char *argv[])
{
	int n, fd;
	char buf[BUFFSIZE];
	char line[MAXLINE];



}

int csopen()
{
	pid_t pid;
	int len;
	char buf[10];
	struct iovec iov[3];
	static int fd[2] = { -1, -1};

	if (fd[0] < 0) {
		if (fd_pipe(fd) < 0) {
		
		}
	
	}
}
