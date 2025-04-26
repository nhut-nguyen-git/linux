#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;

// Signal handler
void signal_handler(int signum) {
    if (signum == SIGINT) {
        sigint_received = 1;
    } else if (signum == SIGTERM) {
        sigterm_received = 1;
    }
}

int main(void) {
    // Set up signal handlers
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Failed to handle SIGINT");
        return EXIT_FAILURE;
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("Failed to handle SIGTERM");
        return EXIT_FAILURE;
    }

    printf("Program started. Type something or press Ctrl+C to send SIGINT.\n");
    printf("Send SIGTERM to terminate the program (e.g., `kill -15 <pid>`).\n");

    while (1) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int ready = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

        if (ready == -1) {
            if (errno == EINTR) {
                // Interrupted by signal, continue loop
                continue;
            } else {
                perror("select() error");
                exit(EXIT_FAILURE);
            }
        }

        if (ready > 0) {
            if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                char buffer[256];
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    printf("You entered: %s", buffer);
                }
            }
        }

        // Check signals
        if (sigint_received) {
            printf("\nSIGINT received.\n");
            sigint_received = 0;
        }

        if (sigterm_received) {
            printf("\nSIGTERM received. Exiting...\n");
            break;
        }
    }

    return 0;
}