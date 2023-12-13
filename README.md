# Shell remoto

En este repositorio se encuentran algunos códigos en C que pueden servir de apoyo al desarrollo de un shell remoto que sigue el esquema cliente/servidor. 
La siguiente gráfica muestra lo que se espera sea la interacción entre el shell cliente y el servidor. 

<img src="figures/MiniShellRemoto.png" alt="Mini Shell Remoto Cliente/Servidor" width="650"/>

Al lado derecho de la gráfica se observa el servidor quien está esperando por peticiones de un cliente.
Este servidor espera recibir comandos a través de la red de parte de un proceso cliente.

El cliente es un proceso que está en espera de leer por teclado un comando y una vez recibido ese comando, se envía al servidor.
El cliente creará un hijo quien se encarga de interactuar con el servidor, enviar el comando y esperar por la respuesta del comando.
Una vez este proceso hijo reciba la respuesta del servidor, imprime la respuesta y termina su ejecución.
El cliente (padre) volverá a presentar el *prompt* (`>`) y quedará en espera del siguiente comando por parte del usuario.

El servidor al recibir una solicitud a través de la red, crea un proceso hijo quien se encargará de procesar dicha solicitud. 
El proceso hijo recibe la solicitud y la ejecuta con la función `execvp` o alguna de las funciones miembros de la familia `exev*`.
El proceso (padre) toma la salida del proceso hijo y la envía al lado del cliente.

---

A continuación se da una descripción de diferentes funciones que le permitirán concentrarse en la lógica de su aplicación y obviar algunos detalles propios del lenguaje C.

## `archivo.c` y `archivo.h`

Estos archivos contienen la definición de las funciones ([`archivo.h`](archivo.h)) y su correspondiente implementación ([`archivo.c`](archivo.c)).
Al interior de [`archivo.h`](archivo.h) se encuntra una descripción corta de las funciones y de los parámetros que estas reciben. 
Así mismo, el archivo [`archivo_main.c`](archivo_main.c) tiene un programa en C el cual es una aplicación que evidencia el uso de las funciones definidas e implementadas en `archivo.h` y `archivo.c`, respectivamente.

Para ver en operación las funciones se ejecuta el comando

```
make archivo
```

Esta ejecución generará el aplicativo `archivo_main` que podrá ser ejecutado desde la línea de comandos escribiendo en esta `./archivo_main`.

## `leercadena.c` y `leercadena.h`

Estos archivos contienen la definición de las funciones ([`leercadena.h`](leercadena.h)) y su correspondiente implementación ([`leercadena.c`](leercadena.c)).
Al interior de [`leercadena.h`](leercadena.h) se encuntra una descripción corta de las funciones y de los parámetros que estas reciben. 
Así mismo, el archivo [`leercadena_main.c`](leercadena_main.c) tiene un programa en C que genera una aplicación donde se muestra como se pueden usar las funciones definidas e implementadas en `leercadena.h` y `leercadena.c`, respectivamente.

Para ver en operación las funciones se ejecuta el comando

```
make leercadena
```

Esta ejecución generará el aplicativo `leercadena_main` que podrá ser ejecutado desde la línea de comandos escribiendo en esta `./leercadena_main`.


## `tcp.c` y `tcp.h`

Estos archivos contienen la definición de las funciones ([`tcp.h`](tcp.h)) y su correspondiente implementación ([`tcp.c`](tcp.c)).
Al interior de [`tcp.h`](tcp.h) se encuntra una descripción corta de las funciones y de los parámetros que estas reciben. 

Para evidenciar el uso de estas funciones se han desarrollado algunos ejemplos que muestran las funciones en operación.

### `basic_client` y `basic_server` 

Para ver en operación este ejemplo se debe ejecutar el comando `make basic_client_server` que se encarga de compilar los archivos objeto que requiere este aplicativo (`tcp.o`) y el cliente (`basic_client`) y el servidor (`basic_server`). 

Para ejecutar el servidor ejecute el comando `basic_server 12358`. 

Abra otra terminal y en ella ejecute el cliente de la siguiente manera `./basic_client localhost 12358`.

El cliente envía la cadena `hola mundo` y esta es recibida por el servidor quien lo imprime en su pantalla.

### `file_client` y `file_server` 

Para ver en operación este ejemplo se debe ejecutar el comando `make file_client_server` que se encarga de compilar los archivos objeto que requiere este aplicativo (`tcp.o`) y el cliente (`file_client`) y el servidor (`file_server`). 

Para ejecutar el servidor ejecute el comando `file_server 12358 tcp.c`. 
El servidor apenas reciba una solicitud, enviará el archivo `tcp.c` al cliente.

Abra otra terminal y en ella ejecute el cliente de la siguiente manera `./file_client localhost 12358 demo.c`.
Una vez se ejecute, el cliente recibirá el archivo del servidor y lo almacenará con el nombre `demo.c`.

<!--
## Elementos que quedan pendientes

* Manejar los errores que se puedan presentar a la hora de ejecutar un comando al lado del servidor. El cliente debe ver ese error.

* Se debe implementar el cambio de directorio emitido desde el cliente y este se vea reflejado en el servidor. Es decir, que se posibilite el cambio de directorio.

* Brindar soporte para la ejecución de comandos compuestos y unidos por el *pipe* (`|`).

* Brindar soporte para la redirección de la salida de la ejecución de un comando. Esta redirección deberá residir al lado del cliente. Quizá se requiera un preprocesamiento del lado del cliente de modo que se haga conciencia que la salida no irá a pantalla sino a un archivo.
-->

