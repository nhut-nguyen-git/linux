#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    char *mode = getenv("MODE"); // Get the MODE environment variable

    if (mode == NULL) {
        printf("MODE environment variable is not set. Exiting...\n");
        return 1;
    }

    pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        printf("Child Process: My PID is %d\n", getpid());

        if (mode[0] == '1') {
            printf("Executing 'ls -l'\n");
            char *args[] = {"ls", "-l", NULL};
            execvp("ls", args);
        } else if (mode[0] == '2') {
            printf("Executing 'date'\n");
            char *args[] = {"date", NULL};
            execvp("date", args);
        } else {
            printf("Invalid MODE value. Use 1 for 'ls -l' or 2 for 'date'.\n");
        }

        // If execvp() fails
        perror("exec failed");
        exit(1);
    } else { // Parent process
        wait(NULL); // Wait for the child process to complete
        printf("Parent Process: Child has completed execution.\n");
    }

    return 0;
}