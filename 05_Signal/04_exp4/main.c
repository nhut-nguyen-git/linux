#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler for SIGTSTP
void handle_sigtstp(int signum) {
    (void)signum; // avoid unused parameter warning
    printf("\nSIGTSTP ignored\n");
}

int main(void) {
    // Register signal handler
    if (signal(SIGTSTP, handle_sigtstp) == SIG_ERR) {
        perror("Failed to set signal handler");
        return EXIT_FAILURE;
    }

    printf("Program is running. Press Ctrl+Z to test SIGTSTP.\n");

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}