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

#define MAX_CONNECTIONS 5

void handle_connection(int client_fd)
{
    char buffer[1000];
    int bytes_read = 0;
    printf("Connection received.\n");
    bytes_read = read(client_fd, buffer, sizeof(buffer));
    write(client_fd, buffer, bytes_read);
}

int main(int argc, char *argv[])
{
    int PORT = 8000; // Random port number

    // Verify arguments
    if ((argc > 3))
    {
        printf("Incorrect number of arguments.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if ((argc > 1) && (strcmp(argv[1], "-p") != 0))
    {
        printf("Wrong arguments passed.\n");
        printf("2nd optional argument should be '-p' and 3rd argument should be a port number.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (argc == 2)
    {
        printf("Incorrect number of arguments.\n");
        printf("Please also provide a port number if you use the optional '-p' argument.\n");
        printf("Usage: %s <-p>(optional) <port_number>(optional)\n", argv[0]);
        exit(1);
    }

    if (argc == 3)
    {
        PORT = atoi(argv[2]);
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET = IPv4
    // SOCK_STREAM = TCP
    // 0 = protocol for IP (Internet Protocol)

    // NOTE : Check if this is the correct sock struct to use for bind()
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;         // AF_INET = IPv4
    sock_addr.sin_port = htons(PORT);       // htons() = host to network short
    sock_addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = any IP address

    int returnval = 0;

    // Bind socket to port
    // Requires sending pointer to sockaddr_in struct typecasted to sockaddr
    returnval = bind(server_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));

    returnval = listen(server_fd, MAX_CONNECTIONS);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Await for a connection on a server_fd. When a connection arrives, open a new socket to communicate with it
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    printf("Connection established.\n");

    char buffer[1000];
    int bytes_read = 0;

    handle_connection(client_fd);

    return 0;
}