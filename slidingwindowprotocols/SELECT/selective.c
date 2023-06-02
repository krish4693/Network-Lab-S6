#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include<time.h>

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
    int expectedAck = 0;

    while (true) {
        // Send frames within the window
        while (nextSeqNum < base + WINDOW_SIZE) {
            sendFrame(nextSeqNum);
            nextSeqNum++;
        }

        // Wait for acknowledgments or timeout
        sleep(TIMEOUT);

        // Check acknowledgments
        for (int i = base; i < nextSeqNum; i++) {
            if (receiveAck(i)) {
                printf("Frame %d acknowledged\n", i);

                if (i == expectedAck) {
                    expectedAck++;
                    base++;
                }
            } else {
                printf("Frame %d not acknowledged\n", i);
                printf("Retransmitting frame: %d\n", i);
                sendFrame(i);
            }
        }
    }

    return 0;
}
