// Kshitij Pingle
// kpingle@csu.fullerton.edu
// Date: November 4, 2024
// Description: Program to simulate an echo server.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[]) {
    // printf("Hello, World!\n");
    int PORT = 7890;

    // Verify arguments
    if ((argc < 2) || (argc > 4)) {
        printf("ERROR0: Incorrect number of arguments.\n");
        printf("Usage: %s <message> <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (argc == 3) {
        printf("ERROR1: Incorrect number of arguments.\n");
        printf("Please also provide a port number if you use the optional '-p' argument.\n");
        printf("Usage: %s <message> <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if ((argc == 4) && (strcmp(argv[2], "-p") != 0)) {
        printf("ERROR2: Incorrect arguments passed.\n");
        printf("3rd optional argument should be '-p' and 4th argument should be a port number.\n");
        printf("Usage: %s <message> <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[2], "-p") == 0) {
        PORT = atoi(argv[3]);
    }

    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    // AF_LOCAL = used for communication between processes on the same machine
    // SOCK_STREAM = TCP
    // 0 = protocol for IP (Internet Protocol)


    // NOTE : Check if this is the correct sock struct to use
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_LOCAL;            // AF_LOCAL = local communication
    sock_addr.sin_port = htons(PORT);           // htons() = host to network short
    sock_addr.sin_addr.s_addr = INADDR_ANY;     // INADDR_ANY = any IP address

    
    // Bind socket to port
    bind(sockfd, (struct sockaddr *) &sock_addr, sizeof(sock_addr));


    listen(sockfd, 1); // 1 = number of connections allowed


    // Await for a connection on a sockfd. When a connection arrives, open a new socket to communicate with it
    int new_sock = accept(sockfd, NULL, NULL); 

    char buffer[1000];
    // int bytes_read = read(new_sock, buffer, sizeof(buffer));
    int bytes_read = 0;

    // Use read() till we get a '\n'
    // while (buffer[bytes_read - 1] != '\n') {
    //     bytes_read += read(new_sock, buffer + bytes_read, sizeof(buffer) - bytes_read);
    // }
    do {
        bytes_read += read(new_sock, buffer, 1);    // Read 1 byte at a time
    } while(buffer[bytes_read - 1] != '\n');
    

    return 0;
}