#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
	struct hostent *ht = NULL;
	char ip[16];
	ht = gethostbyname(argv[1]);
	if (NULL == ht) {
		return -1;
	}

	if (inet_ntop(ht->h_addrtype, ht->h_addr, ip, sizeof(ip))) {
		printf("ip=%s\n", ip);
		return 0;
	} else {
		return -1;
	}
}
