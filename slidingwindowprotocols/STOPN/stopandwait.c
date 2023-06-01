#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>    // time()

// Simulating sending a frame
void sendFrame(int frameNumber) {
    printf("Sending frame: %d\n", frameNumber);
}

// Simulating receiving an acknowledgment
bool receiveAck() {
    // Simulating a random ACK generation
    srand(time(NULL));
    return rand() % 2 == 0;
}

int main() {
    int frameNumber = 0;
    
    while (true) {
        // Send the frame
        sendFrame(frameNumber);
        
        // Wait for acknowledgment
        sleep(1);  // Simulating network delay
        
        if (receiveAck()) {
            // Frame acknowledged, move to the next frame
            frameNumber++;
        } else {
            // Frame not acknowledged, retransmit the current frame
            printf("Frame not acknowledged. Retransmitting frame: %d\n", frameNumber);
        }
    }
    
    return 0;
}
