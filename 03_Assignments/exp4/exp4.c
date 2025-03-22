#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    char cModeExit;
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

    
    if (pid == 0) {         
		// Child process
        printf("Child process started (PID: %d)\n", getpid());

        if ((mode[0] >= '0') && (mode[0] <= '2')) {
            cModeExit = mode[0] - '0';
			      printf("Child process (PID: %d) exiting with status %d\n", getpid(), cModeExit);
			      exit(cModeExit);
		    }
		    else {
			      printf("Invalid MODE value");		
        } 
    }
    else { 
		    int status;
        printf("Parent process (PID: %d) waiting for child (PID: %d)...\n", getpid(), pid);

        // Wait for the child to terminate
        wait(&status);

        // Check if child exited normally
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Parent: Child (PID: %d) exited with status %d\n", pid, exit_code);
        } 
		    else {
            printf("Parent: Child (PID: %d) did not terminate normally\n", pid);
        }
    }
    return 0;
}