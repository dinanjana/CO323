/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void StringToUpper( char st []){

	int i,len;
	len = strlen(st);
	for(i = 0 ; i < len ; i++){

		if(isalpha(st[i])){

			st[i] = toupper(st[i]);
		}

	}



}


int main(int argc, char**argv)
{
	int sockfd,n,noOfMesgs;

	struct sockaddr_in servaddr, cliaddr;

	socklen_t len;
	
	char mesg1 [5];

	char ack[] = "ack";	
	
	char mesg[1000];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);
	
	n=recvfrom(sockfd,mesg1,1000,0,(struct
		sockaddr*)&cliaddr,&len);
	sendto(sockfd,ack,5,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	
	mesg1[n] = 0;
	
	noOfMesgs = mesg1[0] - '0' ;
	
	printf("Received:%d\n", noOfMesgs);
	
	int i = 1;
	while(i <= noOfMesgs){	
		n=recvfrom(sockfd,mesg,1000,0,(struct
		sockaddr*)&cliaddr,&len);
		printf("Received: %s\n",mesg);
		StringToUpper(mesg);		
		
		sendto(sockfd,mesg,n,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		mesg[n] = 0;
		
		i++;
	}

return 0;
}

