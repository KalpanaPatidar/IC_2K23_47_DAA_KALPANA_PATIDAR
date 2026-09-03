# Lab Activity: Algorithm Performance Analyzer

## Problem Statement

Develop an analyzer that compares theoretical and experimental complexity for different sorting algorithms. The analyzer must test best, average, and worst-case inputs, measure execution time for different input sizes, verify sorted output, store results in a file, and generate performance graphs.

## Algorithm / Approach

The program compares Bubble Sort, Insertion Sort, Merge Sort, Quick Sort, and Heap Sort. For each input size, it creates three datasets:

- Best case: already sorted values.
- Average case: reproducible pseudo-random values.
- Worst case: reverse-sorted values.

Each algorithm receives a fresh copy of the same dataset. Timing includes only the sorting call. Every output is checked with `std::is_sorted` and compared with a reference produced by `std::sort`. The average of three repetitions is written to `performance_results.csv`.

## Pseudocode / Flowchart

Pseudocode is in `docs/algorithm-pseudocode/`. Flowchart source is in `docs/algorithm-flowcharts/`.

```text
for each input size n:
    create best, average, and worst input
    for each input case:
        create sorted reference
        for each algorithm:
            repeat three times:
                copy input
                start timer
                sort copy
                stop timer
                verify copy against reference
            write average time and verification result to CSV
run plot_performance.py to create performance_graphs.png
```

## Time and Space Complexity Analysis

| Algorithm | Best Time | Average Time | Worst Time | Extra Space |
|---|---:|---:|---:|---:|
| Bubble Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Insertion Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n^2) | O(log n) average, O(n) worst |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |

Quick Sort uses the final element as its pivot, so sorted and reverse-sorted inputs demonstrate its quadratic worst case. The actual observed time also depends on hardware, compiler, optimization level, and system load.

## Sample Input / Output

The program generates input internally. A sample console record is:

```text
Merge Sort | Average | n = 1000 | 42.31 us | verified = true
Quick Sort | Worst | n = 1000 | 612.44 us | verified = true
```

## Experimental Results

The analyzer records one row per algorithm, case, and input size in `performance_results.csv`. The graph script reads this file and creates `performance_graphs.png` with separate best, average, and worst-case plots.

## Screenshots / Graphs

Run the commands below to generate the graph. Add the resulting `performance_graphs.png` to a lab submission or screenshot section.

## Learning Outcomes

- Relate asymptotic complexity to measured execution time.
- Construct controlled best, average, and worst-case inputs.
- Use repeated timing and CSV data collection for experimental analysis.
- Verify algorithm output before accepting performance results.
- Interpret how algorithm design affects growth as `n` increases.

## Run

From this folder:

```text
python -m pip install -r requirements.txt
g++ -std=c++17 -O2 -Wall -Wextra -pedantic performance_analyzer.cpp -o performance_analyzer.exe
performance_analyzer.exe
python plot_performance.py
```