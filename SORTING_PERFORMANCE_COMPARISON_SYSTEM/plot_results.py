import csv
from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt


def read_results(path: Path):
    results = defaultdict(lambda: [[], []])
    with path.open(newline="") as csv_file:
        for row in csv.DictReader(csv_file):
            if row["sorted"].lower() != "true":
                raise ValueError(f"Unsorted output recorded for {row['algorithm']} at n={row['n']}")
            results[row["algorithm"]][0].append(int(row["n"]))
            results[row["algorithm"]][1].append(float(row["average_time_microseconds"]))
    return results


def main():
    folder = Path(__file__).resolve().parent
    results = read_results(folder / "sorting_results.csv")

    plt.figure(figsize=(10, 6))
    for algorithm, (sizes, times) in results.items():
        plt.plot(sizes, times, marker="o", linewidth=2, label=algorithm)

    plt.title("Merge Sort vs Quick Sort vs Heap Sort")
    plt.xlabel("Input size (n)")
    plt.ylabel("Average execution time (microseconds)")
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig(folder / "sorting_time_comparison.png", dpi=160)
    print("Saved sorting_time_comparison.png")


if __name__ == "__main__":
    main()