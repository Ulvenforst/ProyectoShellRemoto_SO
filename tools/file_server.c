#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "tcp.h"

#define MAX 80

int main(int argc, char *argv[]) 
{ 
    int socket, connfd;  
    int puerto;
    char *filename;
    char ack[MAX_TCP_ACK] = {0};

    if (argc != 3) {
        printf("Uso: %s <puerto> <archivo>\n",argv[0]);
        return 1;
    }

    puerto = atoi(argv[1]);
    filename = argv[2];

    socket = TCP_Server_Open(puerto);
    connfd = TCP_Accept(socket);

    TCP_Write_String(connfd, filename); 
    Recv_ACK(connfd);
    TCP_Send_File(connfd,filename);

    close(socket); 
} 

