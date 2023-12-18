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
#include "../tools/leercadena.h"
#include "../tools/archivo.h"
#include <sys/wait.h>

#define MIN_PORT 1025
#define MAX_PORT 65535

// Prototipos de funciones
void validar_puerto(t_port port);
int iniciar_servidor(t_port port);
void manejar_cliente(int connfd);

int main(int argc, char *argv[])
{
  int sockfd, connfd;
  t_port puerto;

  if (argc != 2)
  {
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
void validar_puerto(t_port port)
{
  if (port < MIN_PORT || port > MAX_PORT)
  {
    fprintf(stderr, "Puerto fuera de rango. Utiliza un puerto entre %d y %d.\n", MIN_PORT, MAX_PORT);
    exit(EXIT_FAILURE);
  }
}

int iniciar_servidor(t_port port)
{
  int socket = TCP_Server_Open(port);
  if (socket < 0)
  {
    fprintf(stderr, "Error al abrir el socket del servidor.\n");
    exit(EXIT_FAILURE);
  }
  return socket;
}

void manejar_cliente(int connfd) {
  char buff[BUFSIZ];
  char comando[BUFSIZ + FILENAMELENGTH + 10];

  printf("Esperando comandos del cliente...\n");
  while (1) {
    bzero(buff, BUFSIZ);
    int n = TCP_Read_String(connfd, buff, BUFSIZ);
    Send_ACK(connfd);

    if (n <= 0) {
      printf("Cliente desconectado o error de lectura.\n");
      break;
    }

    printf("Comando recibido del cliente: %s\n", buff);

    pid_t pid = fork();
    if (pid < 0) {
      fprintf(stderr, "Fork failed");
      exit(EXIT_FAILURE);
    }
    if (pid == 0) { // Proceso hijo
      sprintf(comando, "%s > ejecucion", buff);
      system(comando);

      FILE *archivo = fopen("ejecucion", "r");
      if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
      }

      // Verifica si el archivo está vacío
      fseek(archivo, 0, SEEK_END); 
      if (ftell(archivo) == 0) {
        system(buff);
      }

      TCP_Send_File(connfd, "ejecucion");
      borrar_archivo("ejecucion");
      exit(EXIT_SUCCESS);
    } else { // Proceso padre
      wait(NULL);
    }
  }
}
