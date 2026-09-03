#include <iostream>
#include <vector>

int linearSearch(const std::vector<int>& values, int target) {
	for (int index = 0; index < static_cast<int>(values.size()); ++index) {
		if (values[index] == target) {
			return index;
		}
	}

	return -1;
}

int main() {
	const std::vector<int> values{12, 7, 25, 9, 18};
	const int target = 25;

	std::cout << "Index: " << linearSearch(values, target) << '\n';
	return 0;
}
