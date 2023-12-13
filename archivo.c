#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int cat_archivo(char* filename){
  FILE *fp;
  char buffer[BUFSIZ];

  fp = fopen(filename,"r");
  if (fp == NULL) {
    fprintf(stderr, "Fallo en abrir archivo (cat_archivo) %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  while (fgets(buffer,BUFSIZ,fp) != NULL) {
    printf("%s",buffer);
    bzero(buffer,BUFSIZ);
  }
  fclose(fp);
}

int borrar_archivo(char* filename) {
  return remove(filename);
}

void generar_nombre_archivo(int size, char* filename) {
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (size) {
      --size;
      for (size_t n = 0; n < size; n++) {
          int key = rand() % (int) (sizeof charset - 1);
          filename[n] = charset[key];
      }
      filename[size] = '\0';
  }
}
