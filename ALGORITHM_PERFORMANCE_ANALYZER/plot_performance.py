import csv
from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt


def load_results(path):
    results = defaultdict(lambda: defaultdict(lambda: [[], []]))
    with path.open(newline="") as csv_file:
        for row in csv.DictReader(csv_file):
            if row["verified"].lower() != "true":
                raise ValueError(f"Verification failed: {row}")
            algorithm = row["algorithm"]
            case_name = row["case"]
            results[case_name][algorithm][0].append(int(row["n"]))
            results[case_name][algorithm][1].append(float(row["average_time_microseconds"]))
    return results


def main():
    folder = Path(__file__).resolve().parent
    results = load_results(folder / "performance_results.csv")
    algorithms = sorted({algorithm for case in results.values() for algorithm in case})

    figure, axes = plt.subplots(1, 3, figsize=(16, 5), sharey=True)
    for axis, case_name in zip(axes, ("Best", "Average", "Worst")):
        for algorithm in algorithms:
            sizes, times = results[case_name][algorithm]
            axis.plot(sizes, times, marker="o", label=algorithm)
        axis.set_title(f"{case_name}-case input")
        axis.set_xlabel("Input size (n)")
        axis.grid(True, alpha=0.3)
    axes[0].set_ylabel("Average execution time (microseconds)")
    axes[-1].legend(loc="upper left", fontsize="small")
    figure.suptitle("Algorithm Performance Analyzer")
    figure.tight_layout()
    figure.savefig(folder / "performance_graphs.png", dpi=160)
    print("Saved performance_graphs.png")


if __name__ == "__main__":
    main()