#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define N 128

int main(int argc, const char *argv[])
{
	int sockfd, acceptfd, type, port, nbyte;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[N] = {0};
	socklen_t addrlen = sizeof(struct sockaddr);

	if (0 == strncmp(argv[1], "udp", sizeof("udp"))) {
		type = SOCK_DGRAM; 
	} else if (0 == strncmp(argv[1], "tcp", sizeof("tcp"))) {
		type = SOCK_STREAM;
	} else {
		printf("%s protocol isn't supported ", argv[1]);
	}

	sscanf(argv[2], "%d", &port);
	printf("port=%d\n", port);

	sockfd = socket(AF_INET, type, 0);
	if(sockfd < 0)
	{
		perror("fail to socket");
		return -1;
	}

	//	printf("sockfd = %d\n", sockfd);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[3]); //
	serveraddr.sin_port = htons(port);

	if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) < 0)
	{
		perror("fail to bind");
		return -1;
	}

	if (SOCK_STREAM == type) {
		if(listen(sockfd, 5) < 0)
		{
			perror("fail to listen");
			return -1;
		}


		if((acceptfd = accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen)) < 0)
		{
			perror("fail to accept");
			return -1;
		}

		printf("clientaddr: %s --> %d \n", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	} else if (SOCK_DGRAM == type) {
		while(1)
		{
			if((nbyte = recvfrom(sockfd, buf, N, 0,(struct sockaddr *)&clientaddr, &addrlen)) < 0)
			{
				perror("fail to recvfrom");
				return -1;
			}

			printf("client: %s --> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			printf("client:%s\n", buf);

		}
	}

	close(sockfd);
	return 0;
}

