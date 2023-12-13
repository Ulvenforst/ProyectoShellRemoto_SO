all: basic_client_server shell_client_server file_client_server archivo leercadena

basic_client_server: basic_client basic_server

basic_client: tcp.o
	gcc -o basic_client basic_client.c tcp.o

basic_server: tcp.o
	gcc -o basic_server basic_server.c tcp.o

file_client_server: file_client file_server

file_client: tcp.o
	gcc -o file_client file_client.c tcp.o

file_server: tcp.o
	gcc -o file_server file_server.c tcp.o

tcp.o:
	gcc -c tcp.c

# ---
# Para compilar la prueba de leercadena
#
leercadena: leercadena.o 
	gcc -o leercadena_main leercadena_main.c leercadena.o

leercadena.o:
	gcc -c leercadena.c

# ---

# ---
# Para compilar archivo_main
#
archivo: archivo.o
	gcc -o archivo_main archivo_main.c archivo.o

archivo.o:
	gcc -c archivo.c

# ---

# ---
# Para compilar el shell_client
#

shell_client: leercadena.o archivo.o tcp.o
	gcc -o shell_client shell_client.c leercadena.o archivo.o tcp.o

# ---
# Para compilar el shell_server
#

shell_server: leercadena.o archivo.o tcp.o
	gcc -o shell_server shell_server.c leercadena.o archivo.o tcp.o

shell_client_server: shell_client shell_server

clean:
	rm -f tcp.o basic_client basic_server file_client file_server leercadena_main leercadena.o shell_client shell_server archivo_main archivo.o
