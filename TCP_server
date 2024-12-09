#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *response = "Hello from server";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read data from the client
    read(new_socket, buffer, 1024);
    printf("Client: %s\n", buffer);

    // Send a response to the client
    send(new_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    // Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}
