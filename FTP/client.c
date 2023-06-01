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
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];
    FILE *fp;
    size_t bytesRead;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
        error("Error opening socket.");

    // Set server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        error("Error connecting to the server.");

    // Open the file to send
    fp = fopen("file_to_send.txt", "r");
    if (fp == NULL)
        error("Error opening the file.");

    // Read file data and send to server
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        if (send(clientSocket, buffer, bytesRead, 0) < 0)
            error("Error sending file to server.");
    }

    // Close file and socket
    fclose(fp);
    close(clientSocket);

    printf("File sent successfully!\n");

    return 0;
}
