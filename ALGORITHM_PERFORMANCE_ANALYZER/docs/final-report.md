# Final Report: Algorithm Performance Analyzer

## Objective

Compare theoretical and experimental complexity for several sorting algorithms.

## Implementation

The C++ analyzer generates controlled input cases, measures only the sorting operation with `std::chrono::steady_clock`, verifies every result, and writes CSV records. The Python script converts those records into a three-panel performance graph.

## Findings

The expected trend is that Bubble Sort and Insertion Sort become impractical more quickly for large inputs, while Merge Sort, Quick Sort, and Heap Sort scale more effectively. Quick Sort's result depends strongly on pivot selection, which is visible in its worst-case input measurements.

## Evidence

- Source: `performance_analyzer.cpp`
- Data: `performance_results.csv`
- Graph: `performance_graphs.png`
- Complexity table: `docs/complexity-analysis/sorting-complexity.md`

## Conclusion

Experimental measurements support the theoretical growth rates, although absolute times vary with hardware, compiler settings, and background system activity.