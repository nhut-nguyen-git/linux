#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Signal handler for the child process
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Child process (%d) received SIGUSR1 from parent!\n", getpid());
    }
}

int main() {
    printf("Calling fork() to create a child process...\n");
    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { 
        // Child process
        printf("Child process started (PID: %d)\n", getpid());

        // Set up the signal handler for SIGUSR1
        signal(SIGUSR1, signal_handler);

        // Wait for a signal from the parent
        pause();

        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    } 
    else { 
        // Parent process
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        sleep(3); // Wait 3 seconds before sending the signal

        // Send SIGUSR1 signal to the child process
        kill(pid, SIGUSR1);
        printf("Parent process sent SIGUSR1 to child (PID: %d)\n", pid);

        // Wait for the child process to exit (prevents zombie process)
        waitpid(pid, NULL, 0);
        printf("Parent process collected child process (PID: %d)\n", pid);
    }

    return 0;
}