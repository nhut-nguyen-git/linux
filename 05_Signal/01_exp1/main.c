#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 0; // Bi?n d?m s? l?n nh?n tín hi?u SIGINT

void handle_sigint(int sig) {
    (void)sig; // Tránh warning unused parameter

    sigint_count++;
    printf("SIGINT received (%d/3)\n", sigint_count);

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting program.\n");
        exit(EXIT_SUCCESS);
    }

    // Ðang ký l?i signal handler sau m?i l?n x? lý
    signal(SIGINT, handle_sigint);
}

int main() {
    // Ðang ký hàm handle_sigint cho tín hi?u SIGINT
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    printf("Program is running. Press Ctrl+C to send SIGINT.\n");

    while (1) {
        pause(); // Ð?i tín hi?u
    }

    return 0;
}