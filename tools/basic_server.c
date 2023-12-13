#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"

#define MAX 80

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	bzero(buff,MAX);
	TCP_Read_String(sockfd, buff, MAX); 
	printf("Se leyo %s\n",buff);
} 

// Driver function 
int main(int argc, char *argv[]) 
{ 
	int socket, connfd;  
	int puerto;

	if (argc != 2) {
		printf("Uso: %s <puerto>\n",argv[0]);
		return 1;
	}
	
	puerto = atoi(argv[1]);

	socket = TCP_Server_Open(puerto);
	connfd = TCP_Accept(socket);

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(socket); 
} 

