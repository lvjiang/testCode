#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PID_FILE "/var/run/file.pid"

int unique_check()
{
	char buf[64];
	struct flock lock;
	size_t pidlen = 0;
	ssize_t nbytes = 0;
	int lock_fd = -1;
	int ret = -1;

	lock_fd = open(PID_FILE, O_WRONLY|O_CREAT);
	if (-1 == lock_fd) {
		printf("111111111111111111\n");
		perror("GA:");
		return ret;
	}

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	if (fcntl(lock_fd, F_SETLK, &lock) < 0) {
		printf("222222222222222222222\n");
		perror("GA:");
		goto out;
	}

	snprintf (buf, sizeof(buf), "%d\n", getpid());
	pidlen = strlen(buf);

	nbytes = write (lock_fd, buf, pidlen);
	if (nbytes != (ssize_t)pidlen) {
		printf("33333333333333333333333333\n");
		goto out;
	}
	printf("4444444444444444444444444\n");
	ret = 0;
out:
	//      close(lock_fd);
    return ret;
}
	

int main(void)
{
	
//	daemon(0, 0);

	if (0 != unique_check()) {
		printf("exist\n");
		return 0;
	}	
	
	while(1) {
		printf("gagagag\n");
		sleep(10);
	}

	return 0;
}
