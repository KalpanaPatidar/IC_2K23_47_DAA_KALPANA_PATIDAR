# Sorting Performance Comparison System

This system compares Merge Sort, Quick Sort, and Heap Sort using the same randomly generated input values.

## Workflow

1. `benchmark.cpp` generates random arrays for multiple values of `n`.
2. Each algorithm sorts a fresh copy of the same input.
3. Output is verified with `std::is_sorted` and against a `std::sort` reference.
4. Execution time is averaged over five repetitions and written to `sorting_results.csv`.
5. `plot_results.py` creates `sorting_time_comparison.png` from the CSV data.

## Run

From this folder:

```text
g++ -std=c++17 -O2 -Wall -Wextra -pedantic benchmark.cpp -o benchmark.exe
benchmark.exe
python plot_results.py
```

The generated CSV records each algorithm, input size, average time in microseconds, and verification status.