#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "img.h"

#define SERVER_PORT 12345           // Server port
#define BUFFER_SIZE 1024            // Buffer size for incoming messages

void run_server() {
    int sockfd, client_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    short int buffer[BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return;
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(sockfd);
        return;
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        close(sockfd);
        return;
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Accept incoming connection
        client_addr_len = sizeof(client_addr);
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_sockfd == -1) {
            perror("accept");
            close(sockfd);
            return;
        }

        // Print client information
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("New connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

        // Receive and print messages from client
        ssize_t bytes_received;
        while ((bytes_received = recv(client_sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
            buffer[bytes_received] = '\0';
            bitmap_info_header_t ih;
            if (save_bmp("received.bmp", &ih, buffer)) {
                fprintf(stderr, "main: BMP image not saved.\n");
                return;
            }
            //printf("Received message: %s\n", buffer);
        }

        if (bytes_received == -1) {
            perror("recv");
        }

        // Close the connection
        close(client_sockfd);
        printf("Connection closed by %s:%d\n", client_ip, ntohs(client_addr.sin_port));
    }

    close(sockfd);
}

int main() {
    run_server();
    return 0;
}
