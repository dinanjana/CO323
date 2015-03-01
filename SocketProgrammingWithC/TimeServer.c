/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <time.h>
int main(int argc, char**argv)
{
	int sockfd,n;

	struct sockaddr_in servaddr, cliaddr;

	socklen_t len;

	char mesg[1000];

	//char* banner = "Hello UDP client! This is UDP server";

	time_t current_time;
    	char* c_time_string;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);

	clock_t strt_tmr;
  	strt_tmr = clock();
	
	n=recvfrom(sockfd,mesg,1000,0,(struct
	sockaddr*)&cliaddr,&len);
	printf("Received: %s\n",mesg);
	while(1){	
		
		
		
		 	/* Obtain current time as seconds elapsed since the Epoch. */
    			current_time = time(NULL);
 
    			/* Convert to local time format. */
    			c_time_string = ctime(&current_time);
	
			sendto(sockfd,c_time_string,n,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
			mesg[n] = 0;
			
			sleep(1);
			
		
	}

return 0;
}
