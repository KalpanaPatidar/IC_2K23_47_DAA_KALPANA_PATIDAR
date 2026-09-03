# Sorting Analyzer Pseudocode

```text
algorithms = [Bubble, Insertion, Merge, Quick, Heap]
cases = [Best, Average, Worst]
sizes = [100, 500, 1000, 2000, 5000]

for n in sizes:
    for case in cases:
        input = generateInput(n, case)
        expected = standardSort(input)
        for algorithm in algorithms:
            total = 0
            verified = true
            repeat three times:
                values = copy(input)
                start = clock()
                algorithm(values)
                total += clock() - start
                verified = verified and isSorted(values) and values == expected
            write(algorithm, case, n, total / 3, verified)
```