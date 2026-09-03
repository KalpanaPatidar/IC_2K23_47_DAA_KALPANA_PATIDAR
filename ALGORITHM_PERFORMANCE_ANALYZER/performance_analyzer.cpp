#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using SortFunction = std::function<void(std::vector<int>&)>;

void bubbleSort(std::vector<int>& values) {
    for (int end = static_cast<int>(values.size()) - 1; end > 0; --end) {
        bool swapped = false;
        for (int index = 0; index < end; ++index) {
            if (values[index] > values[index + 1]) {
                std::swap(values[index], values[index + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

void insertionSort(std::vector<int>& values) {
    for (int index = 1; index < static_cast<int>(values.size()); ++index) {
        const int current = values[index];
        int position = index - 1;
        while (position >= 0 && values[position] > current) {
            values[position + 1] = values[position];
            --position;
        }
        values[position + 1] = current;
    }
}

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

void mergeSortRange(std::vector<int>& values, int left, int right) {
    if (left >= right) {
        return;
    }
    const int middle = left + (right - left) / 2;
    mergeSortRange(values, left, middle);
    mergeSortRange(values, middle + 1, right);
    mergeRanges(values, left, middle, right);
}

void mergeSort(std::vector<int>& values) {
    mergeSortRange(values, 0, static_cast<int>(values.size()) - 1);
}

int partition(std::vector<int>& values, int low, int high) {
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

void quickSortRange(std::vector<int>& values, int low, int high) {
    if (low >= high) {
        return;
    }
    const int pivotIndex = partition(values, low, high);
    quickSortRange(values, low, pivotIndex - 1);
    quickSortRange(values, pivotIndex + 1, high);
}

void quickSort(std::vector<int>& values) {
    quickSortRange(values, 0, static_cast<int>(values.size()) - 1);
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

std::vector<int> createInput(int size, const std::string& caseName,
                             std::mt19937& generator) {
    std::vector<int> values(size);
    if (caseName == "Best") {
        for (int index = 0; index < size; ++index) {
            values[index] = index;
        }
    } else if (caseName == "Worst") {
        for (int index = 0; index < size; ++index) {
            values[index] = size - index;
        }
    } else {
        for (int& value : values) {
            value = static_cast<int>(generator());
        }
    }
    return values;
}

struct Result {
    std::string algorithm;
    std::string caseName;
    int n;
    double microseconds;
    bool verified;
};

Result measure(const std::string& algorithm, const std::string& caseName,
               const SortFunction& sort, const std::vector<int>& input,
               int repetitions) {
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());
    double total = 0.0;
    bool verified = true;

    for (int repetition = 0; repetition < repetitions; ++repetition) {
        std::vector<int> values = input;
        const auto start = std::chrono::steady_clock::now();
        sort(values);
        const auto finish = std::chrono::steady_clock::now();
        total += std::chrono::duration<double, std::micro>(finish - start).count();
        verified = verified && std::is_sorted(values.begin(), values.end()) && values == expected;
    }

    return {algorithm, caseName, static_cast<int>(input.size()), total / repetitions, verified};
}

int main() {
    const std::vector<int> sizes{100, 500, 1000, 2000, 5000};
    const std::vector<std::string> cases{"Best", "Average", "Worst"};
    const std::vector<std::pair<std::string, SortFunction>> algorithms{
        {"Bubble Sort", bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Merge Sort", mergeSort},
        {"Quick Sort", quickSort},
        {"Heap Sort", heapSort}};
    constexpr int repetitions = 3;
    std::mt19937 generator(20260903);
    std::ofstream output("performance_results.csv");
    if (!output) {
        std::cerr << "Could not create performance_results.csv\n";
        return 1;
    }

    output << "algorithm,case,n,average_time_microseconds,verified\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int n : sizes) {
        for (const std::string& caseName : cases) {
            const std::vector<int> input = createInput(n, caseName, generator);
            for (const auto& algorithmEntry : algorithms) {
                const std::string& algorithm = algorithmEntry.first;
                const SortFunction& sort = algorithmEntry.second;
                const Result result = measure(algorithm, caseName, sort, input, repetitions);
                output << result.algorithm << ',' << result.caseName << ',' << result.n << ','
                       << result.microseconds << ',' << std::boolalpha << result.verified << '\n';
                std::cout << result.algorithm << " | " << result.caseName << " | n = "
                          << result.n << " | " << result.microseconds << " us | verified = "
                          << std::boolalpha << result.verified << '\n';
                if (!result.verified) {
                    return 1;
                }
            }
        }
    }
    return 0;
}