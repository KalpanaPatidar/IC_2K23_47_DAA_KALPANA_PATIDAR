#include <iostream>
#include <vector>

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

int main() {
    std::vector<int> values{12, 11, 13, 5, 6};
    insertionSort(values);

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}