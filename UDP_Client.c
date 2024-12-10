#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char *message = "Hello from client";
    char buffer[BUFFER_SIZE];
    socklen_t server_addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Send message to server
    sendto(sock_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, server_addr_len);
    printf("Message sent to server\n");

    // Receive response from server
    int n = recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
    buffer[n] = '\0'; // Null-terminate the received message
    printf("Server: %s\n", buffer);

    // Close the socket
    close(sock_fd);

    return 0;
}
