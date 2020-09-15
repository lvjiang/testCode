#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int print_hostent(struct hostent *ht)
{
	char dst[INET_ADDRSTRLEN];
	printf("%s\t", ht->h_name ? ht->h_name : "noname");
/*	while (*ht->h_aliases) {
		printf("%s\t", *ht->h_aliases);
		ht->h_aliases++;
	}*/
	printf("%s\t", ht->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");
	printf("%d\t", ht->h_length);
/*
	while(*ht->h_addr_list) {
		printf("%s\t", *ht->h_addr_list);
		ht->h_addr_list++;
	}
*/
	inet_ntop(ht->h_addrtype, *ht->h_addr_list, dst, sizeof(INET_ADDRSTRLEN));
	printf("%s\t", dst);
	return 0;
}

int print_hostent2(struct hostent *ht)
{
	char **aliases = NULL;
	char **addr_list = NULL;
	char dst[INET_ADDRSTRLEN];

	printf("%s\t", ht->h_name ? ht->h_name : "noname");
	printf("%s\t", ht->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");
	printf("%d\t", ht->h_length);

	for (aliases = ht->h_aliases; *aliases; aliases++) {
		printf("%s\t", *aliases);
	}

	printf("%X\t", *(int *)(*(ht->h_addr_list)));

	for (addr_list = ht->h_addr_list; *addr_list; addr_list++) {
		printf("%s\t", inet_ntop(ht->h_addrtype, *addr_list, dst, sizeof(dst)));
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	struct hostent *ht = NULL;
	
	while (ht = gethostent()) {
		if (ht) {
			print_hostent2(ht);
			printf("\n");
		}
	}

	return 0;
}
