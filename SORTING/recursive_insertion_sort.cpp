#include <iostream>
#include <vector>

void recursiveInsertionSort(std::vector<int>& values, int length) {
    if (length <= 1) {
        return;
    }

    recursiveInsertionSort(values, length - 1);

    const int current = values[length - 1];
    int position = length - 2;
    while (position >= 0 && values[position] > current) {
        values[position + 1] = values[position];
        --position;
    }
    values[position + 1] = current;
}

int main() {
    std::vector<int> values{12, 11, 13, 5, 6};
    recursiveInsertionSort(values, static_cast<int>(values.size()));

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}