/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char no[5]; //= "3";

	char recvline[1000];

	if (argc != 2)
	{
		printf("usage:%s <IP address>\n",argv[0]);
		return -1;
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(32000);
	
	//reading the number of lines
	scanf ("%[^\n]%*c", no);

	sendto(sockfd,no,strlen(no),0,(struct sockaddr
	*)&servaddr,sizeof(servaddr));
	
	n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
	recvline[n]=0;
	printf("Received: %s\n",recvline);
	
	//reading strings to send

	int i = 1;
	
	int num = no[0] - '0';
	char sendline[1000] ; 

	while(i <= num){
	
		
		scanf ("%[^\n]%*c", sendline);
	
	
		sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr
		*)&servaddr,sizeof(servaddr));
		n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
		recvline[n]=0;
		printf("Received: %s\n",recvline);
		i++;
	}
return 0;
}