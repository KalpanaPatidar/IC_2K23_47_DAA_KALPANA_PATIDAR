#include <iostream>
#include <utility>
#include <vector>

void selectionSort(std::vector<int>& values) {
    for (int start = 0; start < static_cast<int>(values.size()) - 1; ++start) {
        int smallest = start;

        for (int index = start + 1; index < static_cast<int>(values.size()); ++index) {
            if (values[index] < values[smallest]) {
                smallest = index;
            }
        }

        if (smallest != start) {
            std::swap(values[start], values[smallest]);
        }
    }
}

int main() {
    std::vector<int> values{64, 25, 12, 22, 11};
    selectionSort(values);

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}