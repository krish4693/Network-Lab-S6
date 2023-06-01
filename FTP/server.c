#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientLength;
    char buffer[BUFFER_SIZE];
    FILE *fp;
    size_t bytesRead;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        error("Error opening socket.");

    // Set server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        error("Error binding socket.");

    // Listen for client connections
    if (listen(serverSocket, 5) < 0)
        error("Error listening for connections.");

    printf("Server started. Listening on port %d...\n", PORT);

    // Accept incoming connection
    clientLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLength);
    if (clientSocket < 0)
        error("Error accepting connection.");

    // Open file to save received data
    fp = fopen("received_file.txt", "w");
    if (fp == NULL)
        error("Error opening file to save received data.");

    // Receive data and write to the file
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytesRead, fp);
    }

    // Close file and sockets
    fclose(fp);
    close(clientSocket);
    close(serverSocket);

    printf("File received successfully!\n");

    return 0;
}
