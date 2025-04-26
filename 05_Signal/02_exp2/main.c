#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_SECONDS 10
#define ALARM_INTERVAL 1

volatile sig_atomic_t elapsed_seconds = 0;

void handle_sigalrm(int sig) {
    (void)sig;  // Ignore unused parameter warning

    elapsed_seconds++;
    printf("Timer: %d seconds\n", elapsed_seconds);

    if (elapsed_seconds >= MAX_SECONDS) {
        printf("Timer reached %d seconds. Exiting program.\n");
        exit(EXIT_SUCCESS);
    }

    // Set next alarm
    alarm(ALARM_INTERVAL);
}

int main(void) {
    printf("Timer started. Counting seconds...\n");

    // Register signal handler for SIGALRM
    if (signal(SIGALRM, handle_sigalrm) == SIG_ERR) {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    // Set initial alarm
    alarm(ALARM_INTERVAL);

    // Infinite loop waiting for signals
    while (1) {
        pause(); // Wait until a signal is caught
    }

    return 0;
}