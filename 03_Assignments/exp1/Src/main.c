#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "common.h"  // Include the static library header

int main() {
    pid_t pid;
    int num1 = 10, num2 = 5;

    printf("Calling fork() to create a child process...\n");

    pid = fork(); // Creating a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        printf("Child Process: My PID is %d\n", getpid());
        printf("Child Process: Performing addition: %d + %d = %d\n", num1, num2, add(num1, num2));
    } else { // Parent process
        wait(NULL); // Wait for the child process to complete (prevents a zombie process)
        printf("Parent Process: My PID is %d\n", getpid());
        printf("Parent Process: My child's PID is %d\n", pid);
        printf("Parent Process: Performing subtraction: %d - %d = %d\n", num1, num2, sub(num1, num2));
    }

    return 0;
}
