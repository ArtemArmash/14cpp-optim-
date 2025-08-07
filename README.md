# C++ Multithreaded Array Summation with an RAII Timer

This C++ project is a practical demonstration of high-performance computing techniques. It shows how to use multithreading to significantly accelerate a computationally intensive task: calculating the sum of all elements in a massive array. The project also features a clever `Timer` class that uses the RAII (Resource Acquisition Is Initialization) pattern to automatically measure the execution time of its scope.

## About The Project

The goal of this program is to compare the performance of a parallel algorithm against a single-threaded one (implicitly). By dividing the array into four chunks and assigning each chunk to a separate thread, the total summation can be completed much faster on a multi-core processor.

### Key Concepts Demonstrated

*   **Multithreading (`std::thread`)**: The core of the project is the use of `std::thread` to launch four worker threads that execute their tasks in parallel.
*   **Performance Optimization**: A clear example of a "divide and conquer" strategy where a large problem is broken down into smaller, independent sub-problems to be solved concurrently.
*   **RAII (Resource Acquisition Is Initialization)**: The `Timer` class is a perfect example of this C++ pattern. Its constructor is called at the beginning of the scope, starting a high-resolution clock. Its destructor is automatically called at the end of the scope, stopping the clock and printing the elapsed time. This guarantees that the time is measured correctly, even if errors were to occur.
*   **High-Resolution Timing (`std::chrono`)**: The use of the `<chrono>` library for accurate, platform-independent time measurement.
*   **Lambda Expressions**: Compact, anonymous functions are used to cleanly pass the workload to each `std::thread`.
*   **Dynamic Memory Management**: A large array is allocated on the heap using `new[]` and deallocated with `delete[]`.

## How It Works

1.  **Timer Starts**: An instance of the `Timer` class is created at the beginning of `main`. Its constructor immediately captures the starting time point.
2.  **Data Preparation**: A very large integer array (one billion elements) is dynamically allocated and filled with random values.
3.  **Thread Creation**: Four threads (`th1`, `th2`, `th3`, `th4`) are created. Each thread is assigned a lambda function that calls a specific `MathX` function. Each `MathX` function is responsible for summing one-quarter of the array.
4.  **Parallel Execution**: The four threads run concurrently, each calculating a partial sum for its portion of the array.
5.  **Synchronization (`join`)**: The main thread calls the `join()` method on each of the worker threads. This forces the main thread to pause and wait until all four threads have completed their calculations.
6.  **Result Aggregation**: Once all threads are finished, the main thread computes the final total by adding the four partial sums (`res1 + res2 + res3 + res4`).
7.  **Timer Stops**: As the `main` function is about to exit, the `Timer` object goes out of scope. Its destructor is automatically invoked, which captures the end time, calculates the duration, and prints the total execution time to the console.

## How to Build and Run

You will need a C++ compiler that supports C++11 or newer (for `std::thread` and `std::chrono`).

1.  Save the code as `Timer.cpp`.
2.  Open a terminal or command prompt in that directory.
3.  Compile the code. **Note**: When compiling with `g++` or `clang` on Linux or macOS, you must link the pthread library.

    ```sh
    # For g++ or clang on Linux/macOS
    g++ Timer.cpp -o parallel_sum_app -std=c++11 -pthread
    ```
    *   `-std=c++11`: Ensures C++11 features are enabled.
    *   `-pthread`: Links the necessary library for `std::thread`.

    ```sh
    # For MSVC on Windows (in a Visual Studio command prompt)
    cl Timer.cpp /EHsc
    ```

4.  Run the executable:
    ```sh
    ./parallel_sum_app
    ```

## Performance Discussion

On a multi-core CPU, this parallel approach will be significantly faster than a simple, single-threaded loop that iterates through the entire array. However, for even better performance, one could consider:

*   **Hardware Concurrency**: The number of threads is hardcoded to 4. A more advanced implementation might use `std::thread::hardware_concurrency()` to dynamically choose the optimal number of threads based on the user's machine.
*   **Avoiding False Sharing**: A potential performance bottleneck where multiple threads' result variables (`res1`, `res2`, etc.) are located on the same CPU cache line. When one thread writes to its variable, it can invalidate the cache for the other threads. This can be mitigated by having each thread return its result instead of writing to a shared-scope variable.
```
