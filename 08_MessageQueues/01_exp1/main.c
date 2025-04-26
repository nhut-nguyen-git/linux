#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // for O_* constants
#include <sys/stat.h>   // for mode constants
#include <mqueue.h>     // for mq_* functions
#include <unistd.h>     // for fork()
#include <sys/wait.h>   // for wait()

#define QUEUE_NAME "/my_message_queue"
#define MAX_SIZE 1024

int main() {
    mqd_t mq_descriptor;
    struct mq_attr queue_attributes;
    pid_t child_pid;
    char message[] = "Hello from parent!";
    char buffer[MAX_SIZE];
    ssize_t bytes_read;

    // Set the message queue attributes
    queue_attributes.mq_flags = 0;              // Blocking mode
    queue_attributes.mq_maxmsg = 10;             // Maximum number of messages
    queue_attributes.mq_msgsize = MAX_SIZE;      // Maximum message size
    queue_attributes.mq_curmsgs = 0;             // Number of messages currently queued

    // Create the message queue
    mq_descriptor = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &queue_attributes);
    if (mq_descriptor == (mqd_t) -1) {
        perror("mq_open() failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork() failed");
        mq_close(mq_descriptor);
        mq_unlink(QUEUE_NAME);
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        // Parent process
        if (mq_send(mq_descriptor, message, strlen(message) + 1, 0) == -1) {
            perror("mq_send() failed");
            mq_close(mq_descriptor);
            mq_unlink(QUEUE_NAME);
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent message: %s\n", message);

        // Wait for child process to complete
        wait(NULL);

        // Close and unlink the message queue
        mq_close(mq_descriptor);
        mq_unlink(QUEUE_NAME);
    } else {
        // Child process
        // Open the message queue (already created)
        mqd_t child_mq_descriptor = mq_open(QUEUE_NAME, O_RDONLY);
        if (child_mq_descriptor == (mqd_t) -1) {
            perror("mq_open() failed in child");
            exit(EXIT_FAILURE);
        }

        bytes_read = mq_receive(child_mq_descriptor, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive() failed");
            mq_close(child_mq_descriptor);
            exit(EXIT_FAILURE);
        }

        printf("Child process received message: %s\n", buffer);

        // Close the message queue
        mq_close(child_mq_descriptor);

        exit(EXIT_SUCCESS);
    }

    return 0;
}