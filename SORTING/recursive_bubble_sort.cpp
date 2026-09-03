#include <iostream>
#include <utility>
#include <vector>

void recursiveBubbleSort(std::vector<int>& values, int length) {
    if (length <= 1) {
        return;
    }

    bool swapped = false;
    for (int index = 0; index < length - 1; ++index) {
        if (values[index] > values[index + 1]) {
            std::swap(values[index], values[index + 1]);
            swapped = true;
        }
    }

    if (swapped) {
        recursiveBubbleSort(values, length - 1);
    }
}

int main() {
    std::vector<int> values{64, 34, 25, 12, 22, 11, 90};
    recursiveBubbleSort(values, static_cast<int>(values.size()));

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}