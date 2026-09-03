#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace sorting {

void mergeRanges(std::vector<int>& values, int left, int middle, int right) {
    std::vector<int> merged;
    merged.reserve(right - left + 1);

    int first = left;
    int second = middle + 1;
    while (first <= middle && second <= right) {
        if (values[first] <= values[second]) {
            merged.push_back(values[first++]);
        } else {
            merged.push_back(values[second++]);
        }
    }
    while (first <= middle) {
        merged.push_back(values[first++]);
    }
    while (second <= right) {
        merged.push_back(values[second++]);
    }

    for (int index = 0; index < static_cast<int>(merged.size()); ++index) {
        values[left + index] = merged[index];
    }
}

void mergeSort(std::vector<int>& values, int left, int right) {
    if (left >= right) {
        return;
    }

    const int middle = left + (right - left) / 2;
    mergeSort(values, left, middle);
    mergeSort(values, middle + 1, right);
    mergeRanges(values, left, middle, right);
}

void mergeSort(std::vector<int>& values) {
    mergeSort(values, 0, static_cast<int>(values.size()) - 1);
}

int partition(std::vector<int>& values, int low, int high) {
    const int middle = low + (high - low) / 2;
    std::swap(values[middle], values[high]);
    const int pivot = values[high];
    int smallerEnd = low - 1;

    for (int index = low; index < high; ++index) {
        if (values[index] <= pivot) {
            ++smallerEnd;
            std::swap(values[smallerEnd], values[index]);
        }
    }

    std::swap(values[smallerEnd + 1], values[high]);
    return smallerEnd + 1;
}

void quickSort(std::vector<int>& values, int low, int high) {
    if (low >= high) {
        return;
    }

    const int pivotIndex = partition(values, low, high);
    quickSort(values, low, pivotIndex - 1);
    quickSort(values, pivotIndex + 1, high);
}

void quickSort(std::vector<int>& values) {
    quickSort(values, 0, static_cast<int>(values.size()) - 1);
}

void siftDown(std::vector<int>& values, int root, int end) {
    while (true) {
        const int leftChild = 2 * root + 1;
        if (leftChild >= end) {
            return;
        }

        int largerChild = leftChild;
        const int rightChild = leftChild + 1;
        if (rightChild < end && values[rightChild] > values[leftChild]) {
            largerChild = rightChild;
        }
        if (values[root] >= values[largerChild]) {
            return;
        }

        std::swap(values[root], values[largerChild]);
        root = largerChild;
    }
}

void heapSort(std::vector<int>& values) {
    const int size = static_cast<int>(values.size());
    for (int root = size / 2 - 1; root >= 0; --root) {
        siftDown(values, root, size);
    }
    for (int end = size - 1; end > 0; --end) {
        std::swap(values[0], values[end]);
        siftDown(values, 0, end);
    }
}

}  // namespace sorting

struct BenchmarkResult {
    std::string algorithm;
    int n;
    double averageMicroseconds;
    bool sorted;
};

BenchmarkResult benchmark(const std::string& name,
                          const std::function<void(std::vector<int>&)>& sort,
                          const std::vector<int>& input, int repetitions) {
    double totalMicroseconds = 0.0;
    bool sorted = true;

    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    for (int repetition = 0; repetition < repetitions; ++repetition) {
        std::vector<int> values = input;
        const auto start = std::chrono::steady_clock::now();
        sort(values);
        const auto finish = std::chrono::steady_clock::now();

        totalMicroseconds += std::chrono::duration<double, std::micro>(finish - start).count();
        sorted = sorted && std::is_sorted(values.begin(), values.end()) && values == expected;
    }

    return {name, static_cast<int>(input.size()), totalMicroseconds / repetitions, sorted};
}

int main() {
    const std::vector<int> sizes{1000, 5000, 10000, 25000, 50000, 100000};
    constexpr int repetitions = 5;
    std::mt19937 generator(20260903);
    std::uniform_int_distribution<int> distribution(0, 1'000'000);

    std::ofstream output("sorting_results.csv");
    if (!output) {
        std::cerr << "Could not create sorting_results.csv\n";
        return 1;
    }

    output << "algorithm,n,average_time_microseconds,sorted\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int n : sizes) {
        std::vector<int> input(n);
        for (int& value : input) {
            value = distribution(generator);
        }

        const std::vector<BenchmarkResult> results{
            benchmark("Merge Sort", [](std::vector<int>& values) { sorting::mergeSort(values); }, input, repetitions),
            benchmark("Quick Sort", [](std::vector<int>& values) { sorting::quickSort(values); }, input, repetitions),
            benchmark("Heap Sort", sorting::heapSort, input, repetitions)};

        for (const BenchmarkResult& result : results) {
            output << result.algorithm << ',' << result.n << ','
                   << result.averageMicroseconds << ',' << std::boolalpha
                   << result.sorted << '\n';
            std::cout << result.algorithm << " | n = " << result.n
                      << " | average = " << result.averageMicroseconds
                      << " us | sorted = " << std::boolalpha << result.sorted << '\n';
        }
    }

    return 0;
}