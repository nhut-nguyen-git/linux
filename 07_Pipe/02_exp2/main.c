#include <stdio.h>
#include <unistd.h>     // for fork(), pipe(), read(), write(), close()
#include <stdlib.h>     // for exit()
#include <string.h>     // for strlen(), strcat()
#include <sys/wait.h>   // for wait()

#define BUFFER_SIZE 100

int main() {
    int pipe1_fd[2], pipe2_fd[2];  // pipe1_fd: parent -> child 1, pipe2_fd: child 1 -> child 2
    pid_t child_pid1, child_pid2;
    char message[] = "Hello from parent!";
    char buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    // Create two pipes
    if (pipe(pipe1_fd) == -1 || pipe(pipe2_fd) == -1) {
        printf("pipe() failed");
        exit(EXIT_FAILURE);
    }

    // Fork first child process
    child_pid1 = fork();
    if (child_pid1 < 0) {
        printf("fork() failed");
        exit(EXIT_FAILURE);
    } else if (child_pid1 > 0) {
        // Parent process
        close(pipe1_fd[0]); // Close read end of pipe 1
        close(pipe2_fd[0]); // Close read end of pipe 2
        close(pipe2_fd[1]); // Close write end of pipe 2

        // Write message to pipe 1 (parent -> child 1)
        bytes_written = write(pipe1_fd[1], message, strlen(message) + 1);
        if (bytes_written == -1) {
            printfr("write() failed in parent");
            close(pipe1_fd[1]);
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent %zd bytes: %s\n", bytes_written, message);

        close(pipe1_fd[1]); // Close write end of pipe 1 after sending

        // Wait for both child processes
        wait(NULL);
        wait(NULL);
    } else {
        // First child process
        close(pipe1_fd[1]); // Close write end of pipe 1
        close(pipe2_fd[0]); // Close read end of pipe 2

        // Read message from parent through pipe 1
        bytes_read = read(pipe1_fd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            printf("read() failed in child 1");
            close(pipe1_fd[0]);
            exit(EXIT_FAILURE);
        }

        printf("Child 1 received %zd bytes: %s\n", bytes_read, buffer);

        // Modify the message
        strcat(buffer, " And this is from child 1!");

        // Fork second child process inside child 1
        child_pid2 = fork();
        if (child_pid2 < 0) {
            printf("fork() failed for child 2");
            exit(EXIT_FAILURE);
        } else if (child_pid2 == 0) {
            // Second child process
            close(pipe1_fd[0]); // Close read end of pipe 1
            close(pipe2_fd[1]); // Close write end of pipe 2

            // Read modified message from child 1 through pipe 2
            bytes_read = read(pipe2_fd[0], buffer, BUFFER_SIZE);
            if (bytes_read == -1) {
                printf("read() failed in child 2");
                close(pipe2_fd[0]);
                exit(EXIT_FAILURE);
            }

            printf("Child 2 received %zd bytes: %s\n", bytes_read, buffer);

            close(pipe2_fd[0]); // Close read end of pipe 2 after reading
            exit(EXIT_SUCCESS);
        } else {
            // Still in child 1
            // Write modified message to pipe 2 (child 1 -> child 2)
            bytes_written = write(pipe2_fd[1], buffer, strlen(buffer) + 1);
            if (bytes_written == -1) {
                printf("write() failed in child 1");
                close(pipe2_fd[1]);
                exit(EXIT_FAILURE);
            }

            printf("Child 1 sent %zd bytes: %s\n", bytes_written, buffer);

            close(pipe1_fd[0]); // Close read end of pipe 1 after reading
            close(pipe2_fd[1]); // Close write end of pipe 2 after writing

            wait(NULL); // Wait for second child to finish
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}