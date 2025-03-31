## Explanation
- **Random Array Generation**: Creates `numbers[100]` with values from `1-100`.
- **Thread Execution**:
  - **Even Counter Thread**: Counts even numbers.
  - **Odd Counter Thread**: Counts odd numbers.
- **Synchronization**:
  - Uses `pthread_join` to wait for both threads to complete.
  - **No mutex needed** as each thread works on separate calculations.
