#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <signal.h>

static struct termios save_termios;
static int ttysavefd = -1;
static enum { RESET, RAW, CBREAK } ttystate = RESET;

int
tty_cbreak(int fd)
{
	int err;
	struct termios buf;

	if(ttystate != RESET) {
		errno = EINVAL;
		return (-1);	
	}

	if (tcgetattr(fd, &buf) < 0) {
		return (-1);	
	}
	save_termios = buf;

	buf.c_lflag &= ~(ECHO | ICANON);

	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0) {
		return (-1);	
	}

	if (tcgetattr(fd, &buf) < 0) {
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return(-1);
	}

	if ((buf.c_lflag & (ECHO | ICANON))
		|| buf.c_cc[VMIN] != 1
		|| buf.c_cc[VTIME] != 0) {
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return (-1);
	}

	ttystate = 	CBREAK;
	ttysavefd = fd;
	return (0);
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
	if (ttysavefd >= 0) {
		tty_reset(ttysavefd);
	}
}

struct termios *
tty_termios(void)
{
	return (&save_termios);
}

static void
sig_catch(int signo)
{
	printf("signa caught\n");
	tty_reset(STDIN_FILENO);
	exit(0);
}

int
main(int argc, char *argv[])
{
	int i;
	char c;

	if (signal(SIGINT, sig_catch) == SIG_ERR) {
		printf("signal(SIGINI) error");
		exit(1);
	}
	if (signal(SIGQUIT, sig_catch) == SIG_ERR) {
		printf("signal(SIGQUIT) error");
		exit(1);
	}
	if (signal(SIGTERM, sig_catch) == SIG_ERR) {
		printf("signal(SIGTERM) error");
		exit(1);
	}

	if (tty_raw(STDIN_FILENO) < 0) {
		printf("tty_raw error");
		exit(1);
	}
	printf("Enter raw mode characters, terminate with DELETE\n");
	while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
		if ((c &= 255) == 0177) {
			break;
		}
		printf("%X %o %d\n",c, c, c);
	}

	if (tty_reset(STDIN_FILENO) < 0) {
		printf("tty_reset error\n");
		exit(1);
	}

	if (i < 0) {
		printf("read error");
		exit(1);
	}

	if (tty_cbreak(STDIN_FILENO) < 0) {
		printf("tty_cbreak error");
		exit(1);
	}
	printf("\nEnter cbreak mode characters, terminate with SIGINT");

	while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
		c &= 255;
		printf("%X %o %d\n", c, c, c);
	}

	if (tty_reset(STDIN_FILENO) < 0) {
		printf("tty_reset error\n");
		exit(1);
	}

	if (i < 0) {
		printf("read error");
		exit(1);
	}
	
}
