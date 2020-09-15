#include <unistd.h>

int main(int argc, char *argv[])
{
	char buf[16];
	size_t nbyte;
	nbyte = read(1, buf, sizeof(buf));
	write(0, buf, nbyte);
}
