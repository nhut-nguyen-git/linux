
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
- Run with MODE=2 (Execute date)
``` sh
export MODE=1
./exec_example
```