# Using `pthread.h` to Create and Manage Threads in C

## 1. Creating Two Threads (`pthread_create`)
The `pthread_create()` function is used to create new threads. 

In the program, we have:
```c
pthread_create(&threadHandles[threadIndex], NULL, threadTask, (void *)threadIndex);
```
- `&threadHandles[threadIndex]`: Pointer to `pthread_t`, storing the thread handle.
- `NULL`: Uses default thread attributes.
- `threadTask`: The function executed by the thread.
- `(void *)threadIndex`: Passes the thread index as an argument.

Since `THREAD_COUNT = 2`, the program creates two threads with IDs `0` and `1`.

---

## 2. Thread Execution
Each thread executes the `threadTask` function:
```c
void *threadTask(void *arg) {
    long threadId = (long)arg;
    printf("Thread %ld: Hello from thread!\n", threadId);
    pthread_exit(NULL);
}
```
- Converts `arg` to `long` to get the thread ID.
- Prints a message with the thread ID.
- Ends the thread using `pthread_exit(NULL);` to release resources.

---

## 3. Waiting for Threads to Finish (`pthread_join`)
After creating threads, the main program must wait for them to complete before exiting.

Using `pthread_join()`:
```c
pthread_join(threadHandles[threadIndex], NULL);
```
- `pthread_join` blocks the main thread until the specified thread finishes.
- Ensures that the program does not terminate before all threads complete their tasks.

---

## 4. When Does a Thread Terminate?
A thread terminates when:
1. It completes its task and reaches `pthread_exit(NULL);`.
2. It returns from its function.
3. The main program terminates, causing all remaining threads to stop.
4. It is explicitly canceled using `pthread_cancel(thread_id);`.