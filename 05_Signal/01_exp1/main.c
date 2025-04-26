#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 0; // Bi?n d?m s? l?n nh?n t�n hi?u SIGINT

void handle_sigint(int sig) {
    (void)sig; // Tr�nh warning unused parameter

    sigint_count++;
    printf("SIGINT received (%d/3)\n", sigint_count);

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting program.\n");
        exit(EXIT_SUCCESS);
    }

    // �ang k� l?i signal handler sau m?i l?n x? l�
    signal(SIGINT, handle_sigint);
}

int main() {
    // �ang k� h�m handle_sigint cho t�n hi?u SIGINT
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    printf("Program is running. Press Ctrl+C to send SIGINT.\n");

    while (1) {
        pause(); // �?i t�n hi?u
    }

    return 0;
}