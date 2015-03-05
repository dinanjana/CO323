/* Sample TCP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char**argv)
{
	int listenfd,connfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	char* banner = "Hello TCP client! This is TCP server";
	char buffer[100];
	char banner1[1000],ch;
	//char file_name [25] ; //"TCPClient.c";
	char file_size[] = "10000";
	
	/* one socket is dedicated to listening */
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* initialize a sockaddr_in struct with our own address information for
	binding the socket */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(21459);

	/* binding */
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(listenfd,0);
	clilen=sizeof(cliaddr);

	/* accept the client with a different socket. */
	connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen); 
	
	// the uninitialized cliaddr variable is filled in with the
	//n = recvfrom(connfd,buffer,2000,0,(struct sockaddr *)&cliaddr,&clilen);
	
	n = recvfrom(connfd,buffer,100,0,(struct sockaddr *)&cliaddr,&clilen);
	
	char file_name [n] ;
	
	int j = 0;
	//Read the file name
	for(j = 0 ; j < n ; j++){
	
		file_name[j] = buffer [j];
	
	}

	printf("Received file name:%s\n",file_name);
	
	sendto(connfd,file_size,strlen(file_size),0,(struct sockaddr
				*)&cliaddr,sizeof(cliaddr));
	//information of the client by recvfrom function
	FILE *fp;
 
 
   	fp = fopen(file_name,"r"); // read mode
   	
   	if( fp == NULL )
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
 
   	;
   	
   	int i = 0 ;//Start reading the file
   		while( ( ch = fgetc(fp) ) != EOF ){
      		
      			
      			banner1[i] = ch;
      			i++;
      			if(i == 999){
      				
      				sendto(connfd,banner1,strlen(banner1),0,(struct sockaddr
				*)&cliaddr,sizeof(cliaddr));
				i = 0;
      			      			
      			}
			
			
      			
      		}

		sendto(connfd,banner1,i,0,(struct sockaddr
		*)&cliaddr,sizeof(cliaddr));
      		
 
   	fclose(fp);
	buffer[n] = 0;
	
	
return 0;
}
