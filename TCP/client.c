#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Get input from the user
    printf("Enter a string: ");
    scanf("%s",buffer);
    // Remove newline character from the input
    // buffer[strcspn(buffer, "\n")] = '\0';

    // Send the string to the server
    ssize_t bytesSent = write(clientSocket, buffer, BUFFER_SIZE);
    if (bytesSent == -1) {
        perror("write failed");
        exit(EXIT_FAILURE);
    }

    // Close the client socket
    close(clientSocket);

    return 0;
}
