
# 🔹 What Happens to the Original Process After execvp()?

## When execvp() is called in the child process:

- The child process is completely replaced with the new program (e.g., ls -l or date).
- The original child code stops executing, and only the new program runs.
- The parent process remains unaffected and waits for the child to finish.

# 🔹 Compilation and Execution
## Compile the Program
``` sh
make all
```
## Run with Different Environment Variables
- Run with MODE=1 (Execute ls -l)
``` sh
export MODE=1
./exec_example
```
- Output:
``` sh
Child Process: My PID is 3790
Executing 'ls -l'
total 28
-rwxrwxr-x 1 nhut nhut 8696 Thg 3 10 23:14 example_program
-rw-rw-r-- 1 nhut nhut  639 Thg 3 10 23:27 exp2.md
-rw-rw-r-- 1 nhut nhut 1262 Thg 3 10 23:12 main.c
-rw-rw-r-- 1 nhut nhut 3088 Thg 3 10 23:14 main.o
-rw-rw-r-- 1 nhut nhut  255 Thg 3 10 23:11 Makefile
Parent Process: Child has completed execution.
```

- Run with MODE=2 (Execute date)
``` sh
export MODE=1
./exec_example
```

- Output:
``` sh
Child Process: My PID is 3585
Executing 'date'
Thứ hai, 10 Tháng 3 năm 2025 23:14:43 +07
Parent Process: Child has completed execution.

```