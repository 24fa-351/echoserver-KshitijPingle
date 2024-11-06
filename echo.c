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
    int PORT = 8000;        // Random port number

    // Verify arguments
    if ((argc > 3)) {
        printf("Incorrect number of arguments.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if ((argc > 1) && (strcmp(argv[1], "-p") != 0)) {
        printf("Wrong arguments passed.\n");
        printf("2nd optional argument should be '-p' and 3rd argument should be a port number.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (argc == 2) {
        printf("Incorrect number of arguments.\n");
        printf("Please also provide a port number if you use the optional '-p' argument.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (argc == 3) {
        PORT = atoi(argv[2]);
    }


    int server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    // AF_LOCAL = used for communication between processes on the same machine
    // SOCK_STREAM = TCP
    // 0 = protocol for IP (Internet Protocol)


    // NOTE : Check if this is the correct sock struct to use for bind()
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;            // AF_INET = IPv4
    sock_addr.sin_port = htons(PORT);           // htons() = host to network short
    sock_addr.sin_addr.s_addr = INADDR_ANY;     // INADDR_ANY = any IP address

    
    // Bind socket to port
    bind(server_fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr));


    listen(server_fd, 1); // 1 = number of connections allowed


    // Await for a connection on a server_fd. When a connection arrives, open a new socket to communicate with it
    int client_fd = accept(server_fd, NULL, NULL); 

    printf("Connection established.\n");

    char buffer[1000];
    // int bytes_read = read(client_fd, buffer, sizeof(buffer));
    int bytes_read = 0;


    //Put everything in a big while loop which doesn't end until the client sends a message with the word "exit" in it.
        // Also include the accept and close statements in it

    while (strcmp(buffer, "exit\n") != 0) {
        bytes_read = 0;

        do {
            bytes_read += read(client_fd, buffer, 1);    // Read 1 byte at a time
        } while(buffer[bytes_read - 1] != '\n');
        
        printf("Message received: '%s'\n", buffer);
        write(client_fd, buffer, bytes_read);
    }

    close(client_fd);

    return 0;
}