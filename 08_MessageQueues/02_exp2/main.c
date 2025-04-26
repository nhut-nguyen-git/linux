#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // for O_* constants
#include <sys/stat.h>   // for mode constants
#include <mqueue.h>     // for mq_* functions
#include <unistd.h>     // for fork()
#include <sys/wait.h>   // for wait()

#define QUEUE_PARENT_TO_CHILD "/queue_parent_to_child"
#define QUEUE_CHILD_TO_PARENT "/queue_child_to_parent"
#define MAX_SIZE 1024

int main() {
    mqd_t mq_parent_to_child;
    mqd_t mq_child_to_parent;
    struct mq_attr queue_attributes;
    pid_t child_pid;
    char message[] = "Hello from parent to child!";
    char buffer[MAX_SIZE];
    ssize_t bytes_read;
    char count_message[MAX_SIZE];

    // Set message queue attributes
    queue_attributes.mq_flags = 0;               // Blocking mode
    queue_attributes.mq_maxmsg = 10;              // Maximum number of messages
    queue_attributes.mq_msgsize = MAX_SIZE;       // Maximum message size
    queue_attributes.mq_curmsgs = 0;              // Number of messages currently queued

    // Create message queues
    mq_parent_to_child = mq_open(QUEUE_PARENT_TO_CHILD, O_CREAT | O_RDWR, 0644, &queue_attributes);
    if (mq_parent_to_child == (mqd_t) -1) {
        perror("mq_open() failed for parent to child");
        exit(EXIT_FAILURE);
    }

    mq_child_to_parent = mq_open(QUEUE_CHILD_TO_PARENT, O_CREAT | O_RDWR, 0644, &queue_attributes);
    if (mq_child_to_parent == (mqd_t) -1) {
        perror("mq_open() failed for child to parent");
        mq_close(mq_parent_to_child);
        mq_unlink(QUEUE_PARENT_TO_CHILD);
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork() failed");
        mq_close(mq_parent_to_child);
        mq_close(mq_child_to_parent);
        mq_unlink(QUEUE_PARENT_TO_CHILD);
        mq_unlink(QUEUE_CHILD_TO_PARENT);
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        // Parent process
        if (mq_send(mq_parent_to_child, message, strlen(message) + 1, 0) == -1) {
            perror("mq_send() failed from parent");
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent message: %s\n", message);

        // Wait for child to complete
        wait(NULL);

        // Read character count from child
        bytes_read = mq_receive(mq_child_to_parent, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive() failed in parent");
            exit(EXIT_FAILURE);
        }

        printf("Parent process received character count: %s\n", buffer);

        // Close and unlink the message queues
        mq_close(mq_parent_to_child);
        mq_close(mq_child_to_parent);
        mq_unlink(QUEUE_PARENT_TO_CHILD);
        mq_unlink(QUEUE_CHILD_TO_PARENT);
    } else {
        // Child process
        // Open existing message queues
        mqd_t child_mq_parent_to_child = mq_open(QUEUE_PARENT_TO_CHILD, O_RDONLY);
        if (child_mq_parent_to_child == (mqd_t) -1) {
            perror("mq_open() failed in child for reading");
            exit(EXIT_FAILURE);
        }

        mqd_t child_mq_child_to_parent = mq_open(QUEUE_CHILD_TO_PARENT, O_WRONLY);
        if (child_mq_child_to_parent == (mqd_t) -1) {
            perror("mq_open() failed in child for writing");
            mq_close(child_mq_parent_to_child);
            exit(EXIT_FAILURE);
        }

        // Receive message from parent
        bytes_read = mq_receive(child_mq_parent_to_child, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive() failed in child");
            mq_close(child_mq_parent_to_child);
            mq_close(child_mq_child_to_parent);
            exit(EXIT_FAILURE);
        }

        printf("Child process received message: %s\n", buffer);

        // Count number of characters
        size_t character_count = strlen(buffer);

        // Prepare character count message
        snprintf(count_message, sizeof(count_message), "%zu", character_count);

        // Send character count back to parent
        if (mq_send(child_mq_child_to_parent, count_message, strlen(count_message) + 1, 0) == -1) {
            perror("mq_send() failed from child");
            mq_close(child_mq_parent_to_child);
            mq_close(child_mq_child_to_parent);
            exit(EXIT_FAILURE);
        }

        // Close message queues
        mq_close(child_mq_parent_to_child);
        mq_close(child_mq_child_to_parent);

        exit(EXIT_SUCCESS);
    }

    return 0;
}