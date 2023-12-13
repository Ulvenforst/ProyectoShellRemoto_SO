#include <stdio.h>
#include "archivo.h"

#define MAX_LENGTH_STRING 20

int main(int argc, char* argv[]) {
  char cadena[MAX_LENGTH_STRING];
  cat_archivo("archivo.c");
  borrar_archivo("borrar.txt");
  generar_nombre_archivo(MAX_LENGTH_STRING,cadena); 
  printf("%s\n",cadena);
  return 0;
}
