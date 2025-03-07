#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *filename = "test.txt";

    // Open file with O_APPEND and O_CREAT (create file if it does not exist)
    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Seek to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Write data to file
    write(fd, "Hello\n", 6);

    // Close file
    close(fd);

    return 0;
}