# File Handling with O_APPEND in C

## Description
This program demonstrates opening a file using the `O_APPEND` flag in C. If the file does not exist, it is automatically created. The program then seeks to the beginning of the file using `lseek()` and attempts to write some data.

## Expected Behavior
Despite seeking to the beginning, the data will always be appended to the end of the file. This happens because the `O_APPEND` flag forces all writes to occur at the file's end, regardless of the file pointer's position.

## Code Implementation

```c
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
```

## Explanation
1. **Opening the file:**
   - `O_WRONLY`: Opens the file for writing only.
   - `O_APPEND`: Ensures all writes occur at the end of the file.
   - `O_CREAT`: Creates the file if it does not exist.
   - `0644`: Sets file permissions (owner can read/write, others can read).

2. **Seeking to the beginning of the file:**
   - `lseek(fd, 0, SEEK_SET);` moves the file pointer to the start of the file.
   - However, due to `O_APPEND`, this does not affect where the data is written.

3. **Writing to the file:**
   - The string "Hello\n" is written to the file.
   - Despite the seek operation, it is appended at the end due to `O_APPEND` behavior.

## Observed Behavior
- If `test.txt` initially contains:
  ```
  Existing Data
  ```
- After running the program, the file will contain:
  ```
  Existing Data
  Hello
  ```
- The new data is always appended to the end, proving that `O_APPEND` overrides `lseek()` when writing.

## Conclusion
- The `O_APPEND` flag ensures all writes occur at the file's end.
- Seeking within the file does not affect the writing position when `O_APPEND` is used.
- This is useful for logging and scenarios where preserving the write order is critical.