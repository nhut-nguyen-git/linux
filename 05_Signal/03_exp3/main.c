#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function for SIGUSR1
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Child process (PID: %d) received signal from parent.\n", getpid());
    }
}

int main() {
    pid_t child_pid;
    int pipefd[2];

    // Create a pipe for synchronization
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This is the child process
        close(pipefd[1]); // Close the write end of the pipe
        signal(SIGUSR1, signal_handler); // Register the signal handler for SIGUSR1
        printf("Child process (PID: %d) is ready to receive signals.\n", getpid());
        // Read a byte from the pipe to know when the parent is ready to send signals
        char ready_signal;
        read(pipefd[0], &ready_signal, 1);
        close(pipefd[0]);
        // Child process will wait indefinitely for signals
        while (1) {
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    } else {
        // This is the parent process
        close(pipefd[0]); // Close the read end of the pipe
        printf("Parent process (PID: %d) created child process (PID: %d).\n", getpid(), child_pid);
        // Send a byte through the pipe to signal the child that the parent is ready
        write(pipefd[1], "1", 1);
        close(pipefd[1]);

        // Send SIGUSR1 to the child process 5 times
        for (int i = 0; i < 5; i++) {
            printf("Parent process (PID: %d) is sending SIGUSR1 signal (count: %d)...\n", getpid(), i + 1);
            kill(child_pid, SIGUSR1);
            sleep(2); // Wait for 2 seconds
        }

        printf("Parent process (PID: %d) has sent SIGUSR1 signal 5 times. Terminating.\n", getpid());
        // Wait for the child process to terminate
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}