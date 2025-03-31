## 1. Why is Mutex Needed?
- Since multiple threads **simultaneously** modify the shared variable (`counter`), a **race condition** may occur.
- Without a **mutex**, different threads may read/update the same memory location **at the same time**, causing **incorrect results**.
- The `pthread_mutex_lock` and `pthread_mutex_unlock` functions ensure **mutual exclusion**, meaning only **one thread at a time** can modify `counter`.

---

## 2. What Happens Without Mutex?
If we remove the mutex:
- The final value of `counter` may be **less than expected** due to **lost updates** (two threads may read the same value before updating it).
- The result is **non-deterministic**—it depends on how the OS schedules the threads.
- The issue is called a **race condition**, leading to **data corruption**.