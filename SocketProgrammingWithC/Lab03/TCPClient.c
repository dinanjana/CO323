/* Sample TCP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char banner[] = "Hello TCP server! This is TCP client";
	char banner1[2000];
	char buffer[1000];
	char file_name[] = "TCPClient.c",ch;
	
		if (argc != 2)
		{

			printf("usage: ./%s <IP address>\n",argv[0]);
			return -1;
		}
	
	/* socket to connect */
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* IP address information of the server to connect to */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(21459);
	
	
 
	
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	sendto(sockfd,file_name,strlen(file_name),0, (struct sockaddr
	*)&servaddr,sizeof(servaddr));
	
	

	n=recvfrom(sockfd,buffer,10000,0,NULL,NULL);
	buffer[n]=0; 
	printf("Received Size:%s\n",buffer);

	int size = buffer[0] - '0';
	//char buffer2[size];
	int i = 0;
	for(i = 0 ; i < size + 1 ; i = i + 1000){

		n=recvfrom(sockfd,buffer,size,i,NULL,NULL);
		//buffer[n]=0;
		
	}

	buffer[n]=0;
	printf("Received:%s\n",buffer2);

return 0;
}
