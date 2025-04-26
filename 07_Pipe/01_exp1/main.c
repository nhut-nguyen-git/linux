#include <stdio.h>
#include <unistd.h>     // fork(), pipe(), read(), write(), close()
#include <stdlib.h>     // exit()
#include <string.h>     // strlen()
#include <sys/wait.h>   // wait()

#define BUFFER_SIZE 100

int main() {
    int pipe_fd[2];               // pipe_fd[0]: read end, pipe_fd[1]: write end
    pid_t child_pid;
    char message[] = "Hello from parent process!";
    char buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe() failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    } 
    else if (child_pid > 0) {
        // Parent process
        close(pipe_fd[0]); // Close unused read end

        bytes_written = write(pipe_fd[1], message, strlen(message) + 1);
        if (bytes_written == -1) {
            perror("write() failed");
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent %zd bytes.\n", bytes_written);

        close(pipe_fd[1]); // Close write end after writing

        wait(NULL); // Wait for child process to finish
    } 
    else {
        // Child process
        close(pipe_fd[1]); // Close unused write end

        bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            perror("read() failed");
            close(pipe_fd[0]);
            exit(EXIT_FAILURE);
        }

        printf("Child process received %zd bytes: %s\n", bytes_read, buffer);

        close(pipe_fd[0]); // Close read end after reading
        exit(EXIT_SUCCESS);
    }

    return 0;
}