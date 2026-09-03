#include <iostream>
#include <utility>
#include <vector>

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
            break;
        }
    }
}

int main() {
    std::vector<int> values{64, 34, 25, 12, 22, 11, 90};
    bubbleSort(values);

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}