/*
Archivo: cliente.c
Autor: Juan Camilo Narváez Tascón <juan.narvaez.tascon@correounivalle.edu.co>
       Juan Esteban Clavijo García <juan.esteban.clavijo@correounivalle.edu.co>
       Óscar David Cuaical <cuaical.oscar@correounivalle.edu.co>
Fecha creación: 14-12-23
Fecha última modificación: 14-12-23
Licencia: GPL-3.0
*/

/**
 * HISTORIA: Se desea crear un bash del lado del cliente que cree un subproceso
 * por cada comando a ejecutar, este comando será enviado al servidor, el cual
 * ejecutará el comando el mandará la respuesta de vuelta al cliente; este la
 * mostrará por pantalla.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../tools/tcp.h"
#include "../tools/leercadena.h"

#define MIN_PORT 1025
#define MAX_PORT 65535

// Prototipos de funciones
void validar_puerto(t_port port);
int establecer_conexion(char *host, t_port port);
void interactuar_con_servidor(int sockfd);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <host> <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convertir y validar el puerto
    t_port port = atoi(argv[2]);
    validar_puerto(port);

    // Establecer la conexión con el servidor
    int sockfd = establecer_conexion(argv[1], port);

    // Interactuar con el servidor
    interactuar_con_servidor(sockfd);

    // Cerrar la conexión
    if (TCP_Close(sockfd) < 0) {
        fprintf(stderr, "Error al cerrar el socket.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// Implementaciones de funciones
void validar_puerto(t_port port) {
    if (port < MIN_PORT || port > MAX_PORT) {
        fprintf(stderr, "Puerto fuera de rango. Utiliza un puerto entre %d y %d.\n", MIN_PORT, MAX_PORT);
        exit(EXIT_FAILURE);
    }
}

int establecer_conexion(char *host, t_port port) {
    printf("Intentando conectar en <%s,%d>\n", host, port);
    int sockfd = TCP_Open(Get_IP(host), port);
    if (sockfd < 0) {
        fprintf(stderr, "Error al abrir el socket TCP.\n");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void interactuar_con_servidor(int sockfd) {
    char cmd[BUFSIZ];
    printf("Conectado al servidor. Escribe 'salir' para terminar.\n");
    while(1) {
        printf("> ");
        fflush(stdout);
        leer_de_teclado(BUFSIZ, cmd);

        // Si el comando es "salir", terminar el bucle
        if (strcmp(cmd, "salir") == 0) {
            break;
        }

        TCP_Write_String(sockfd, cmd); // Enviar comando al servidor
    }
}
