# 🔹 Compilation and Execution
## Compile the Program
``` sh
make all
```
## Run with Different Environment Variables
- Run with MODE=1
``` sh
export MODE=1
./example_program
```
- Output:
``` sh
Parent process (PID: 3212) waiting for child (PID: 3213)...
Child process started (PID: 3213)
Child process (PID: 3213) exiting with status 1
Parent: Child (PID: 3213) exited with status 1
```

- Run with MODE=2 
``` sh
export MODE=2
./example_program
```

- Output:
``` sh
Parent process (PID: 3214) waiting for child (PID: 3215)...
Child process started (PID: 3215)
Child process (PID: 3215) exiting with status 2
Parent: Child (PID: 3215) exited with status 2
```