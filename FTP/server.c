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
    printf("-2");

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        error("Error opening socket.");

    memset(&serverAddress, 0, sizeof(serverAddress));  //sets serverAddress structure values to 0 for all the default structure props
    serverAddress.sin_family = AF_INET;                 //IPV4
    serverAddress.sin_port = htons(PORT);       //PORT IS SET
    serverAddress.sin_addr.s_addr = INADDR_ANY;  //TO RECEIVE ALL TYPES OF CONNECTION(ANY ADDRESS)

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)   //BINDS SERVER ADDRESS TO SERVERSOCKET AND CHECKS IF BINDING WAS SUCCESSFULL OR NOT
        error("Error binding socket.");

    if (listen(serverSocket, 5) < 0)                                 //LISTENING TO INCOMING CLIENT CONNECTIONS
        error("Error listening for connections.");

    printf("Server started. Listening on port %d...\n", PORT);
    // printf("0");

    clientLength = sizeof(clientAddress);
    // printf("1");
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLength);
    // printf("2");

    if (clientSocket < 0)
        error("Error accepting connection.");

    fp = fopen("received_file.txt", "w");
    if (fp == NULL)
        error("Error opening file to save received data.");

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytesRead, fp);
    }

    fclose(fp);
    close(clientSocket);
    close(serverSocket);

    printf("File received successfully!\n");

    return 0;
}
