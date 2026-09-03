# Complexity Analysis

| Algorithm | Best | Average | Worst | Space |
|---|---|---|---|---|
| Bubble Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Insertion Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n^2) | O(log n) average, O(n) worst |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |

Bubble Sort is optimized to stop after a pass with no swaps, giving its best-case O(n) behavior. Quick Sort uses a fixed final-element pivot; this makes already sorted and reverse-sorted arrays worst-case inputs.