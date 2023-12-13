#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tcp.h"

void func(int sockfd) 
{ 
	char *buff = "hola mundo" + '\x0'; 
	TCP_Write_String(sockfd, buff); 
} 

int main(int argc, char* argv[]) 
{ 
	int sockfd, port; 
	char *host;

	if (argc != 3) {
		printf("Uso: %s <host> <puerto>\n",argv[0]);
		return 1;
	}
	host = argv[1];
	port = atoi(argv[2]);

	printf("Looking to connect at <%s,%d>\n",host,port);
	sockfd = TCP_Open(Get_IP(host),port);
	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 
} 

