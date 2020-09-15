#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define  N  8

int main(int argc, const char *argv[])
{
	int sockfd, acceptfd, n,flags;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[N+1];

	if(argc != 3)
	{
		fprintf(stderr,"Usage:%s serverip port.\n", argv[0]);
		return -1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("fail to socket");
		return -1;
	}
	printf("sockfd = %d\n", sockfd);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]); //
	serveraddr.sin_port = htons(atoi(argv[2]));

	if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) < 0)
	{
		perror("fail to bind");
		return -1;
	}

	if(listen(sockfd, 5) < 0)
	{
		perror("fail to listen");
		return -1;
	}

	socklen_t addrlen = sizeof(struct sockaddr);

	if((acceptfd = accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen)) < 0)
	{
		perror("fail to accept");
		return -1;
	}

	printf("clientaddr: %s --> %d \n", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

	while(1)
	{
		if((n = recv(acceptfd, buf, N, 0)) <= 0)
		{
			perror("fail to recv");
			return -1;
		}

		buf[n] = '\0';
		printf("n=%d server:%s\n",n, buf);
		if(strncmp(buf,"quit", 4) == 0)
		{
			break;
		}

		//strcat(buf, " from server.");

		sleep(60);
		if(send(acceptfd, buf, n, 0) < 0)
		{
			perror("fail to send");
			return -1;
		}
	}

	close(acceptfd);
	close(sockfd);
	
	return 0;
}
