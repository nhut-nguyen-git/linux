#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode))
        printf("File Type: Regular file\n");
    else if (S_ISDIR(mode))
        printf("File Type: Directory\n");
    else if (S_ISLNK(mode))
        printf("File Type: Symbolic link\n");
    else
        printf("File Type: Other\n");
}

int main() {
    char *filename = "example.txt";
    char *data = "Hello, this is a test file.";
    int fd;

    // Open the file for writing (create if it doesn't exist, truncate if it does)
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // Write data to file
    if (write(fd, data, 27) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);

    // Get file information using stat
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file stats");
        return 1;
    }
    
    // Print file information
    printf("File Name: %s\n", filename);
    print_file_type(file_stat.st_mode);
    printf("Last Modified Time: %s", ctime(&file_stat.st_mtime));
    printf("File Size: %ld bytes\n", file_stat.st_size);
    
    return 0;
}