#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_zombie() 
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
		//Child process
        printf("Child process (Zombie) created! PID: %d\n", getpid());
        exit(0);  // Child exits immediately
    } 
	else {
        printf("Parent (PID: %d) exiting, leaving zombie child (PID: %d)\n", getpid(), pid);
        sleep(5); // Give time to observe the zombie using `ps aux`
    }
}

void create_orphan() 
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
		//Child process
        sleep(3); // Let parent exit first
        printf("Orphan child (PID: %d) adopted by init/systemd (New PPID: %d)\n", getpid(), getppid());
    } 
	else {
        printf("Parent (PID: %d) exiting, orphaning child (PID: %d)\n", getpid(), pid);
        exit(0); // Parent exits early, making child an orphan
    }
}

int main() 
{
    printf("Creating Zombie Process...\n");
    create_zombie();
    sleep(10); // Pause for observation
    printf("Creating Orphan Process...\n");
    create_orphan();
    sleep(5); // Allow orphaned child time to execute
    return 0;
}