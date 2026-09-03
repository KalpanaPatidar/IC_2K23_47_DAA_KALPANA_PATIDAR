#include <iostream>
#include <vector>

int recursiveBinarySearch(const std::vector<int>& values, int target,
                          int left, int right) {
    if (left > right) {
        return -1;
    }

    const int middle = left + (right - left) / 2;

    if (values[middle] == target) {
        return middle;
    }
    if (values[middle] < target) {
        return recursiveBinarySearch(values, target, middle + 1, right);
    }

    return recursiveBinarySearch(values, target, left, middle - 1);
}

int main() {
    const std::vector<int> sortedValues{3, 8, 12, 17, 24, 31};
    const int target = 24;

    const int lastIndex = static_cast<int>(sortedValues.size()) - 1;
    std::cout << "Index: "
              << recursiveBinarySearch(sortedValues, target, 0, lastIndex)
              << '\n';
    return 0;
}