## Code Explanation

1. **Array Definition**:  
   The array `array[ARRAY_SIZE]` contains 1 million integers. The values are randomly initialized between 0 and 99.

2. **Global Sum Variable**:  
   `global_sum` stores the total sum of the array. Since multiple threads will access this variable, we protect it using a mutex to avoid race conditions.

3. **Mutex**:  
   The `pthread_mutex_t sum_mutex` ensures that only one thread updates the global sum at a time, providing thread safety during the sum calculation.

4. **Partial Sum Function**:  
   The `partial_sum` function is executed by each thread. Each thread computes the sum of a segment of the array and updates the global sum in a thread-safe manner using the mutex.

5. **Thread Creation and Joining**:  
   The program creates 4 threads, each handling one part of the array. After the threads finish their computation, the main program waits for their completion using `pthread_join`.

6. **Mutex Locking and Unlocking**:  
   The threads lock the mutex before updating the global sum and unlock it after updating, ensuring that only one thread modifies `global_sum` at a time.