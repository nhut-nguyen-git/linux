#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MESSAGE_QUEUE_NAME "/three_process_queue"
#define BUFFER_SIZE 1024
#define MESSAGE_PRIORITY 1

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void convert_to_uppercase(char *str) {
    for (int i = 0; str[i]; ++i) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int main() {
    mqd_t mq_descriptor;
    struct mq_attr mq_attributes;
    char buffer[BUFFER_SIZE];
    pid_t child1_pid, child2_pid;

    // Set attributes for the message queue
    mq_attributes.mq_flags = 0; // Blocking mode
    mq_attributes.mq_maxmsg = 10;
    mq_attributes.mq_msgsize = BUFFER_SIZE;
    mq_attributes.mq_curmsgs = 0;

    // Create or open the message queue
    mq_descriptor = mq_open(MESSAGE_QUEUE_NAME, O_CREAT | O_RDWR, 0644, &mq_attributes);
    if (mq_descriptor == (mqd_t)-1) {
        error_exit("mq_open");
    }

    child1_pid = fork();
    if (child1_pid < 0) {
        error_exit("fork child 1");
    }

    if (child1_pid == 0) {
        // Child 1 process
        mqd_t mq_child1;
        char received_message[BUFFER_SIZE];

        mq_child1 = mq_open(MESSAGE_QUEUE_NAME, O_RDWR);
        if (mq_child1 == (mqd_t)-1) {
            error_exit("mq_open in child 1");
        }

        if (mq_receive(mq_child1, received_message, BUFFER_SIZE, NULL) == -1) {
            error_exit("mq_receive in child 1");
        }

        printf("Child 1 received: %s\n", received_message);

        // Convert to uppercase
        convert_to_uppercase(received_message);

        // Send the modified message back to the queue
        if (mq_send(mq_child1, received_message, strlen(received_message) + 1, MESSAGE_PRIORITY) == -1) {
            error_exit("mq_send in child 1");
        }

        mq_close(mq_child1);
        exit(EXIT_SUCCESS);
    }

    child2_pid = fork();
    if (child2_pid < 0) {
        error_exit("fork child 2");
    }

    if (child2_pid == 0) {
        // Child 2 process
        mqd_t mq_child2;
        char modified_message[BUFFER_SIZE];

        mq_child2 = mq_open(MESSAGE_QUEUE_NAME, O_RDWR);
        if (mq_child2 == (mqd_t)-1) {
            error_exit("mq_open in child 2");
        }

        // Wait to receive the modified message
        if (mq_receive(mq_child2, modified_message, BUFFER_SIZE, NULL) == -1) {
            error_exit("mq_receive in child 2");
        }

        printf("Child 2 received and prints: %s\n", modified_message);

        mq_close(mq_child2);
        exit(EXIT_SUCCESS);
    }

    // Parent process
    printf("Parent process: Enter a message to send: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

    if (mq_send(mq_descriptor, buffer, strlen(buffer) + 1, MESSAGE_PRIORITY) == -1) {
        error_exit("mq_send in parent");
    }

    // Wait for both child processes to finish
    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    // Cleanup
    mq_close(mq_descriptor);
    mq_unlink(MESSAGE_QUEUE_NAME);

    printf("Parent process: All child processes have finished.\n");

    return 0;
}