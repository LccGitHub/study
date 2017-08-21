/*************************************************************************
	> File Name: server.c
	> Created Time: Mon 21 Aug 2017 03:06:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>



int main()
{
	int listen_fd = 0;
	int connect_fd = 0;
	struct sockaddr_in sockaddr;
	char  buffer[1024] = {0};
	memset(buffer,0, sizeof(buffer));
	memset(&sockaddr,0,sizeof(sockaddr));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(10004);

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	bind(listen_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

	listen(listen_fd,1024);

	printf("Please wait for the client information.\n");

	for (;;)
	{
		if (connect_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL) == -1) {
			printf("accept socket error :%s errno:%d\n", strerror(errno), errno);
			continue;
		}
		else {
			int cnt = 0;
			cnt = recv(connect_fd, buffer, 1024, 0);
			buffer[cnt] = '\0';
			printf("recv [%d] msg from client : %s\n", connect_fd,buffer);
			close(connect_fd);
		}
	}
	close(listen_fd);
}
