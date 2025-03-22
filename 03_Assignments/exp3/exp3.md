

# 🔹 Compilation and Execution
## Compile the Program
``` sh
make all
```
## Run program
``` sh
./exec_example
```
- Output:
``` sh
Calling fork() to create a child process...
Parent process (PID: 3940), child PID: 3941
Child process started (PID: 3941)
Parent process sent SIGUSR1 to child (PID: 3941)
Child process (3941) received SIGUSR1 from parent!
Child process (PID: 3941) exiting...
Parent process collected child process (PID: 3941)
```

