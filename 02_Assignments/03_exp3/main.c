#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s filename num-bytes [r/w] \"Hello\"\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    char mode = argv[3][0];
    char *content = argv[4];
    
    int fd;
    char buffer[num_bytes + 1];
    
    if (mode == 'r') {
        // Open file for reading
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file for reading");
            return 1;
        }
        
        int bytes_read = read(fd, buffer, num_bytes);
        if (bytes_read == -1) {
            perror("Error reading file");
            close(fd);
            return 1;
        }
        
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        printf("Read content: %s\n", buffer);
        
    } 
    else if (mode == 'w') {
        // Open file for writing (create if not exists, truncate if exists)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file for writing");
            return 1;
        }
        
        if (write(fd, content, num_bytes) == -1) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }
        printf("Successfully wrote to file: %s\n", content);
    
    } 
    else {
        fprintf(stderr, "Invalid mode. Use 'r' for read or 'w' for write.\n");
        return 1;
    }
    
    close(fd);
    return 0;
}