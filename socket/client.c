#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 1024
int main(int argc,char **argv)
{
	char *servInetAddr = "127.0.0.1";
	int socketfd;
	struct sockaddr_in sockaddr;
	char recvline[MAXLINE], sendline[MAXLINE];
	int n;
	socketfd = socket(AF_INET,SOCK_STREAM,0);
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(10004);
	inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);
	if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 ) {
		printf("connect error %s errno: %d\n",strerror(errno),errno);
	}
	
	printf("send message to server\n");
	strcpy(sendline, "Hello server, I am client. \n");
	if((send(socketfd,sendline,strlen(sendline),0)) < 0) {
		printf("send mes error: %s errno : %d",strerror(errno),errno);
	}
	else {
		printf("send mes success\n");
	}
	close(socketfd);
	printf("client exit\n");
	return 0;
}
