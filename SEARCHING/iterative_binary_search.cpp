#include <iostream>
#include <vector>

int iterativeBinarySearch(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    while (left <= right) {
        const int middle = left + (right - left) / 2;

        if (values[middle] == target) {
            return middle;
        }
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

int main() {
    const std::vector<int> sortedValues{3, 8, 12, 17, 24, 31};
    const int target = 17;

    std::cout << "Index: " << iterativeBinarySearch(sortedValues, target) << '\n';
    return 0;
}