#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_flags(struct addrinfo *);
void print_family(struct addrinfo *);
void print_type(struct addrinfo *);
void print_protocol(struct addrinfo *);

int
main (int argc, char *argv[])
{
	struct addrinfo hint;
	struct addrinfo *aip;
	struct addrinfo *res;
	int ret;
	char dst[INET_ADDRSTRLEN];
	char *addr = NULL;
	struct sockaddr_in *sinp;
	
	memset(&hint, 0, sizeof(hint));	
	hint.ai_flags = AI_CANONNAME;
	hint.ai_protocol = IPPROTO_TCP;

	ret = getaddrinfo(argv[1], argv[2], &hint, &res);
	if (ret) {
		printf("getaddrinfo error: %s\n", gai_strerror(ret));	
	}
	
	for (aip = res; aip; aip = aip->ai_next) {
		print_flags(aip);
		print_family(aip);
		print_type(aip);
		print_protocol(aip);

		printf("\n\thost %s", aip->ai_canonname?aip->ai_canonname:"-");
		
		if (aip->ai_family == AF_INET) {
			sinp = (struct sockaddr_in *)aip->ai_addr;
			addr = inet_ntop(AF_INET, &sinp->sin_addr, dst, sizeof(dst));	
			printf(" address %s", addr ? addr:"unknown");
			printf(" port %d", ntohs(sinp->sin_port));
		}
		printf("\n");	
	}

	return 0;
}

void
print_family(struct addrinfo *aip)
{
	printf(" family ");
	switch (aip->ai_family) {
	case AF_INET:
		printf("inet");
		break;
	case AF_INET6:
		printf("inet6");
		break;
	case AF_UNIX:
		printf("unix");
		break;
	case AF_UNSPEC:
		printf("unspecified");
		break;
	default:
		printf("unknown");
	}
}


void
print_type(struct addrinfo *aip)
{
	printf(" type ");
	switch (aip->ai_socktype) {
		case SOCK_STREAM:
			printf("stream");
			break;
		case SOCK_DGRAM:
			printf("datagram");
			break;
		case SOCK_SEQPACKET:
			printf("seqpacket");
			break;
		case SOCK_RAW:
			printf("raw");
			break;
		default:
			printf("unknow (%d)", aip->ai_socktype);
   	}
}

void
print_protocol(struct addrinfo *aip)
{
	printf(" protocl ");
	switch (aip->ai_protocol) {
		case 0:
			printf("default");
			break;
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_RAW:
			printf("RAW");
			break;
		default:
			printf("unknown (%d)", aip->ai_protocol);
			break;
	}
}

void
print_flags(struct addrinfo *aip)
{
	printf(" flags");
	if (aip->ai_flags == 0) {
		printf(" 0");	
	} else {
		if (aip->ai_flags & AI_PASSIVE) {
			printf(" passive");
		}	
		if (aip->ai_flags & AI_CANONNAME) {
			printf(" canonname");
		}	
		if (aip->ai_flags & AI_NUMERICHOST) {
			printf(" numerichost");
		}	
		if (aip->ai_flags & AI_NUMERICSERV) {
			printf(" numericserv");
		}	
		if (aip->ai_flags & AI_V4MAPPED) {
			printf(" v4mapped");
		}	
		if (aip->ai_flags & AI_ALL) {
			printf(" all");
		}	
	}
}
