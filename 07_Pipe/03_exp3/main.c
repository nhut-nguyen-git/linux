#include <stdio.h>
#include <unistd.h>     // for fork(), pipe(), read(), write(), close()
#include <stdlib.h>     // for exit()
#include <string.h>     // for strlen()

#define BUFFER_SIZE 100

int main() {
    int pipe_fd[2];
    pid_t child_pid;
    char message[] = "This is a sample string.";
    char buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        printf("pipe() failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid < 0) {
        printf("fork() failed");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        // Parent process
        close(pipe_fd[0]); // Close read end of the pipe

        // Write message into the pipe
        bytes_written = write(pipe_fd[1], message, strlen(message) + 1);
        if (bytes_written == -1) {
            printf("write() failed in parent");
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent %zd bytes: %s\n", bytes_written, message);

        close(pipe_fd[1]); // Close write end after writing

        wait(NULL); // Wait for the child process to finish
    } else {
        // Child process
        close(pipe_fd[1]); // Close write end of the pipe

        // Read message from the pipe
        bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            printf("read() failed in child");
            close(pipe_fd[0]);
            exit(EXIT_FAILURE);
        }

        printf("Child process received %zd bytes: %s\n", bytes_read, buffer);

        // Count number of characters
        size_t character_count = strlen(buffer);
        printf("Child process counted %zu characters.\n", character_count);

        close(pipe_fd[0]); // Close read end after reading

        exit(EXIT_SUCCESS);
    }

    return 0;
}