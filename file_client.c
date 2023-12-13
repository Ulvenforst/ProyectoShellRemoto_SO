#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include "tcp.h"

int main(int argc, char* argv[]) 
{ 
    int sockfd, port; 
    char *host;
    char *filename;

    if (argc != 4) {
        printf("Uso: %s <host> <puerto> <filename>\n",argv[0]);
        return 1;
    }
    host = argv[1];
    port = atoi(argv[2]);

    printf("Looking to connect at <%s,%d>\n",host,port);
    sockfd = TCP_Open(host,port);

    //filename = (char*)malloc(sizeof(char)*BUFSIZ);
    filename = (char*)calloc(BUFSIZ,sizeof(char));
    assert(filename != NULL);
    TCP_Read_String(sockfd,filename,BUFSIZ); 
    Send_ACK(sockfd);
    printf("Archivo a recibir [%s]\n",filename);
    free(filename);
    filename = argv[3];
    TCP_Recv_File(sockfd, filename); 
    printf("Archivo recibido en archivo [%s]\n",filename);

    close(sockfd); 
} 

