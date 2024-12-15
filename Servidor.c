/*
Grupo: 4CV1
Flores Anzurez Marco Antonio

Comunicación de procesos utilizando sockets
Este es un ejemplo de un servidor y un cliente que se comunican a través de un socket.
*/
// Servidor
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int sock_desc, conn_desc;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[200];

    // Creación del socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    // Configuración de la dirección del servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8888);

    // Vinculación del socket a la dirección del servidor
    bind(sock_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Escucha conexiones
    listen(sock_desc, 20);

    // Acepta conexiones entrantes
    conn_desc = accept(sock_desc, (struct sockaddr*)NULL, NULL);

    // Lee los datos del cliente y los envía de vuelta
    while (1) {
        // Limpia el buffer
        memset(buffer, 0, sizeof(buffer));
        
        // Lee los datos enviados por el cliente
        read(conn_desc, buffer, sizeof(buffer));
        
        // Imprime el mensaje del cliente
        printf("Mensaje del cliente: %s\n", buffer);
        
        // Envía los datos de vuelta al cliente
        write(conn_desc, buffer, strlen(buffer)+1);
    }

    return 0;
}
