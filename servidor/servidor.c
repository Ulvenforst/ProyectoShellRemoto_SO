/*
Archivo: servidor.c
Autor: Juan Camilo Narváez Tascón <juan.narvaez.tascon@correounivalle.edu.co>
       Juan Esteban Clavijo García <juan.esteban.clavijo@correounivalle.edu.co>
       Óscar David Cuaical <cuaical.oscar@correounivalle.edu.co>
Fecha creación: 14-12-23
Fecha última modificación: 14-12-23
Licencia: GPL-3.0
*/

/**
 * HISTORIA: Este bash es el servidor que se encarga de ejecutar los comandos
 * enviados por el cliente, generando una respuesta y enviándola al servidor
 * para ser impresa por pantalla.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../tools/tcp.h"

#define MIN_PORT 1025
#define MAX_PORT 65535

// Prototipos de funciones
void validar_puerto(t_port port);
int iniciar_servidor(t_port port);
void manejar_cliente(int connfd);

int main(int argc, char *argv[]) {
    int sockfd, connfd;
    t_port puerto;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    puerto = atoi(argv[1]);
    validar_puerto(puerto);

    sockfd = iniciar_servidor(puerto);
    connfd = TCP_Accept(sockfd); // Aceptar la conexión del cliente

    manejar_cliente(connfd); // Manejar la interacción con el cliente

    close(sockfd); // Cerrar el socket del servidor
    return 0;
}

// Implementaciones de funciones
void validar_puerto(t_port port) {
    if (port < MIN_PORT || port > MAX_PORT) {
        fprintf(stderr, "Puerto fuera de rango. Utiliza un puerto entre %d y %d.\n", MIN_PORT, MAX_PORT);
        exit(EXIT_FAILURE);
    }
}

int iniciar_servidor(t_port port) {
    int socket = TCP_Server_Open(port);
    if (socket < 0) {
        fprintf(stderr, "Error al abrir el socket del servidor.\n");
        exit(EXIT_FAILURE);
    }
    return socket;
}

void manejar_cliente(int connfd) {
    char buff[BUFSIZ];

    printf("Esperando comandos del cliente...\n");
    while(1) {
        bzero(buff, BUFSIZ); // Limpiar buffer antes de cada lectura

        // Leer mensaje del cliente
        int n = TCP_Read_String(connfd, buff, BUFSIZ);
        if (n <= 0) {
            printf("Cliente desconectado o error de lectura.\n");
            break;
        }
        printf("Comando recibido del cliente: %s\n", buff);

        // Procesar el comando aquí
        // ...

        // Verificar si el comando es para cerrar la conexión
        if (strcmp(buff, "salir") == 0) {
            printf("Comando para terminar la conexión recibido.\n");
            break;
        }
        // Aquí se enviaría la respuesta al cliente
    }
}