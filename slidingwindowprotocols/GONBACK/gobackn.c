#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define WINDOW_SIZE 4
#define TIMEOUT 3

// Simulating sending a frame
void sendFrame(int frameNumber) {
    printf("Sending frame: %d\n", frameNumber);
}

// Simulating receiving an acknowledgment
bool receiveAck(int ackNumber) {
    // Simulating an ACK generation
    srand(time(NULL));
    return rand() % 2 == 0;
}

int main() {
    int frameNumber = 0;
    int base = 0;
    int nextSeqNum = 0;
    
    while (true) {
        // Send frames within the window
        while (nextSeqNum < base + WINDOW_SIZE) {
            sendFrame(nextSeqNum);
            nextSeqNum++;
        }
        
        // Wait for acknowledgment or timeout
        sleep(TIMEOUT);
        
        if (receiveAck(base)) {
            // Frame acknowledged, move the window
            base++;
        } else {
            // Frame not acknowledged, retransmit all frames in the window
            printf("Timeout. Retransmitting frames starting from: %d\n", base);
            nextSeqNum = base;
        }
    }
    
    return 0;
}