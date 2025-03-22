# What is a Zombie Process?

## 🔸 Definition

A Zombie process is a process that has terminated (exited) but still exists in the process table because its parent has not retrieved its exit status using wait().

## 🔸 How Zombies Are Created

A child process is created using fork().

The child exits normally using exit(), but its entry remains in the process table.

The parent does not call wait() to clean up the child process.

The child becomes a Zombie (Z) process.

## 🔸 Observing Zombie Processes

Run the following command to check for zombie processes:

``` sh

ps aux | grep Z
```

A zombie process will appear with a Z (zombie) status in the output.

## 🔸 Why Are Zombies a Problem?

They consume process table entries, which are limited.

If many zombies accumulate, they can slow down the system.

They cannot be killed using kill -9 because they are already dead! The only way to remove them is for the parent process to wait() for them or terminate.

## 🔸 How to Prevent Zombie Processes

Use wait() in the parent to clean up child processes.

Use SIGCHLD signal handler with waitpid() to automatically clean up terminated child processes.

# What is an Orphan Process?

## 🔸 Definition

An Orphan process is a child process whose parent has exited before the child finishes executing.

## 🔸 How Orphans Are Created

A child process is created using fork().

The parent process exits first, while the child is still running.

The child becomes an Orphan process.

init (PID 1) or systemd adopts the orphan to clean it up.

## 🔸 Observing Orphan Processes

Run this command to check the parent PID (PPID) of a process:

``` sh
ps -ef | grep <child_pid>
```

If the PPID is 1, the process is an orphan.

## 🔸 Are Orphans Harmful?

No, they are not harmful because init (or systemd) takes over and manages them.

The Linux system automatically cleans up orphaned processes.