#define _XOPEN_SOURCE 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <signal.h>

#define BUFFSIZE 512
#define OPTSTR "+d:einv"

typedef void (*sighandler_t)(int);

static struct termios save_termios;
static int ttysavefd = -1; 
static enum { RESET, RAW, CBREAK } ttystate = RESET;
static volatile sig_atomic_t sigcaught;

sighandler_t
signal_intr(int signo, sighandler_t func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif
	if (sigaction(signo, &act, &oact) < 0) {
		return (SIG_ERR);
	}

	return(oact.sa_handler);
}

ssize_t
writen(int fd, const void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;

	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) < 0) {
			if (nleft == n) {
				return (-1);
			} else {
				break;
			}
		} else if (nwritten == 0) {
			break;
		}

		nleft -= nwritten;
		ptr += nwritten;    
	}   
	return(n - nleft);
}


int
tty_reset(int fd)
{
	if (ttystate == RESET) {
		return (0);
	}   

	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0) {
		return(-1);
	}   
	ttystate = RESET;
	return (0);
}

void
tty_atexit(void)
{
	if  (ttysavefd >= 0) {
		tty_reset(ttysavefd);
	}
}

int
ptym_open(char *pts_name, int pts_namesz)
{
	char *ptr;
	int fdm,err;

	if ((fdm = posix_openpt(O_RDWR)) < 0) {
		return -1;
	}

	if (grantpt(fdm) < 0) {
		goto errout;	
	}

	if (unlockpt(fdm) < 0) {
		goto errout;	
	}

	if ((ptr = ptsname(fdm)) == NULL) {
		goto errout;	
	}

	strncpy(pts_name, ptr, pts_namesz);
	pts_name[pts_namesz -1] = '\0';
	return fdm;

errout:
	err = errno;
	close(fdm);
	errno = err;
	return -1;
}


int
ptys_open(char *pts_name)
{
	int fds;

	if ((fds = open(pts_name, O_RDWR)) < 0) {
		return (-1);	
	}

	return (fds);
}

pid_t
pty_fork(int *ptrfdm, char *slave_name, int slave_namesz,
		const struct termios *slave_termios,
		const struct winsize *slave_winsize)
{
	int fdm, fds;
	pid_t pid;
	char pts_name[20];

	fdm = ptym_open(pts_name, sizeof(pts_name));
	if (fdm < 0) {
		printf("can't open master pty: %s, error %d", pts_name, fdm);	
	}

	if (slave_name) {
		strncpy(slave_name, pts_name, slave_namesz);
		slave_name[slave_namesz - 1] = '\0';
	}

	pid = fork();
	if ( pid < 0) {
		return (-1);
	} else if (0 == pid) {
		if (setsid() < 0) {
			printf("setsid error\n");	
		}

		fds = ptys_open(pts_name);
		if (fds < 0) {
			printf("can't open slave pty\n");
		}
		close(fdm);

		if (slave_termios) {
			if (tcsetattr(fds, TCSANOW, slave_termios) < 0) {
				 printf("tcsetattr error on slave pty\n");
			}	
		}

		if (slave_winsize) {
			if (ioctl(fds, TIOCSWINSZ, slave_winsize) < 0) {
				printf("TIOCSWINSZ error on slave pty\n");
			}	
		}

		
		if (dup2(fds, STDIN_FILENO) != STDIN_FILENO) {
			printf("dup2 error to stdin\n");
		}
		
		if (dup2(fds, STDOUT_FILENO) != STDOUT_FILENO) {
			printf("dup2 error to stdout\n");
		}

		if (dup2(fds, STDERR_FILENO) != STDERR_FILENO) {
			printf("dup2 error to stderr\n");
		}

		if (fds != STDIN_FILENO && fds != STDOUT_FILENO && fds != STDERR_FILENO) { 
			close(fds);
		}

		return (0);
	} else {
		*ptrfdm = fdm;
		return (pid);	
	}
}

static void
set_noecho(int fd)
{
	struct termios stermios;
	if (tcgetattr(fd, &stermios) < 0) {
		printf("tcgetattr error\n");
	}

	stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

	stermios.c_oflag &= ~(ONLCR);

	if (tcsetattr(fd, TCSANOW, &stermios) < 0) {
		printf("tcsetattr error\n");
	}
}

void
do_driver(char *driver)
{
	pid_t child;
	int fd_pipe[2];

	if (pipe(fd_pipe) < 0) {
		printf("can't create stream pipe\n");
	}

	child = fork();
	if (child < 0) {
		printf("fork error\n");
	} else if (child == 0) {
		close(fd_pipe[1]);

		if (dup2(fd_pipe[0], STDIN_FILENO) != STDIN_FILENO) {
			printf("dup2 error to stdin\n");
		}
		
		if (dup2(fd_pipe[0], STDOUT_FILENO) != STDOUT_FILENO) {
			printf("dup2 error to stdout\n");
		}

		if (dup2(fd_pipe[0], STDERR_FILENO) != STDERR_FILENO) {
			printf("dup2 error to stderr\n");
		}

		if (fd_pipe[0] != STDIN_FILENO && fd_pipe[0] != STDOUT_FILENO && fd_pipe[0] != STDERR_FILENO) { 
			close(fd_pipe[0]);
		}

		execlp(driver, driver, (char *)0);
		printf("execlp error for: %s\n", driver);

	} else {
		close(fd_pipe[0]);

		if (dup2(fd_pipe[1], STDIN_FILENO) != STDIN_FILENO) {
			printf("dup2 error to stdin\n");
		}
		
		if (dup2(fd_pipe[1], STDOUT_FILENO) != STDOUT_FILENO) {
			printf("dup2 error to stdout\n");
		}

		if (dup2(fd_pipe[1], STDERR_FILENO) != STDERR_FILENO) {
			printf("dup2 error to stderr\n");
		}

		if (fd_pipe[1] != STDIN_FILENO && fd_pipe[1] != STDOUT_FILENO && fd_pipe[1] != STDERR_FILENO) { 
			close(fd_pipe[1]);
		}
	}

}

static void
sig_term(int signo)
{
	sigcaught = 1;
}

void
loop(int ptym, int ignoreeof)
{
	pid_t child;
	int nread;
	char buf[BUFFSIZE];

	child = fork();
	if (child < 0) {
		printf("fork error\n");
		exit(1);
	} else if (child == 0) {
		for( ; ; ) {
			nread = read(STDIN_FILENO, buf, BUFFSIZE);	
			if (nread < 0) {
				printf("read error from stdin\n");
				exit(1);
			} else if (nread == 0) {
				break;
			}

			if (writen(ptym, buf, nread) != nread) {
				printf("writen error to master pty\n");
				exit(1);
			}
		}

		if (ignoreeof == 0) {
			kill(getppid(), SIGTERM);
		}
		exit(0);
	}
	
	if (signal_intr(SIGTERM, sig_term) == SIG_ERR) {
		printf("signal_intr error for SIGTERM\n");
		exit(0);
	}

	for ( ; ; ) {
		nread = read(ptym, buf, BUFFSIZE);
		if (nread <= 0) {
			break;
		}

		if (writen(STDOUT_FILENO, buf, nread) != nread) {
			printf("writen error to stdout\n");
		}
	
	}
	
	if (sigcaught == 0) {
		kill(child, SIGTERM);
	}
}

int
tty_raw(int fd)
{
	int err;
	struct termios buf;

	if (ttystate != RESET) {
		errno = EINVAL;
		return (-1);
	}

	if (tcgetattr(fd, &buf) < 0) {
		return(-1);
	}
	save_termios = buf;

	buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); 
	buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	buf.c_cflag &= ~(CSIZE | PARENB);
	buf.c_cflag |= CS8;
	buf.c_oflag &= ~(OPOST);

	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0) {
		return (-1);
	}

	if (tcgetattr(fd, &buf) < 0) {
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return (-1);
	}

	if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) ||
			(buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
			(buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 ||
			(buf.c_oflag & OPOST) ||
			buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0) {

		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return (-1);
	}

	ttystate = RAW;
	ttysavefd = fd;

	return (0);
}


int
main(int argc, char *argv[])
{
	int fdm, c, ignoreeof, interactive, noecho, verbose;
	pid_t pid;
	char *driver;
	char slave_name[20];
	struct termios orig_termios;
	struct winsize size;

	interactive = isatty(STDIN_FILENO);
	ignoreeof = 0;
	noecho = 0;
	verbose = 0;
	driver = NULL;

	opterr = 0;
	while (( c = getopt(argc, argv, OPTSTR)) != EOF) {
		switch (c) {
			case 'd':
				driver = optarg;
				break;	
			case 'e':
				noecho = 1;
				break;
			case 'i':
				ignoreeof = 1;
				break;
			case 'n':
				interactive = 1;
				break;
			case 'v':
				verbose = 1;
				break;
			case '?':
				printf("unrecognized option: -%c", optopt);
				exit(0);
		}
	}

	if (optind >= argc) {
		printf ("useage: pty [ -d driver -einv ] proram [ arg ... ]\n");
	}	

	if (interactive) {
		if (tcgetattr(STDIN_FILENO, &orig_termios) < 0) {
			printf("tcgetattr error on stdin\n");
			exit(1);
		}
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&size) < 0) {
			printf("TIOCGWINSZ error\n");
			exit(1);
		}

		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), &orig_termios, &size);
	} else {
		pid = pty_fork(&fdm, slave_name, sizeof(slave_name), NULL, NULL);
	}

	if (pid < 0) {
		printf("fork error\n");
		exit(1);
	} else if (pid == 0) {
		if (noecho) {
			set_noecho(STDIN_FILENO);
		}	

		if (execvp(argv[optind], &argv[optind]) < 0) {
			printf("can't excute: %s", argv[optind]);
			exit(1);
		}
	}


	if (verbose) {
		fprintf(stderr, "slave name = %s\n", slave_name);
		if (driver != NULL) {
			fprintf(stderr, "driver = %s\n", driver);
		}	
	}

	if (interactive && driver == NULL) {
		if (tty_raw(STDIN_FILENO) < 0) {
			printf("tty_saw error\n");
			exit(1);	
		}

		if (atexit(tty_atexit) < 0) {
			printf("atexit error\n");
			exit(1);
		}
	}

	if (driver) {
		do_driver(driver);
	}

	//loop(fdm, ignoreeof);
	
	exit(0);
}
