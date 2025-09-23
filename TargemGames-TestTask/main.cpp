#include "TargemStringClass.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
	std::vector<String> strings;

	std::cout << "Enter strings (empty line to finish):" << std::endl;
	std::cout << "Example test cases:" << std::endl;
	std::cout << "1. Apple" << std::endl;
	std::cout << "2. banana" << std::endl;
	std::cout << "3. Cherry" << std::endl;
	std::cout << "4. date" << std::endl;
	std::cout << "5. ELEPHANT" << std::endl;
	std::cout << "6. (press enter to finish)" << std::endl << std::endl;

	// strings reading
	std::string input;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);
		if (input.empty()) {
			break;
		}
		strings.push_back(String(input.c_str()));
	}

	if (strings.empty()) {
		std::cout << "No strings entered. Using default test data..." << std::endl;
		
		const char* test_data[] = {
			"Apple", "banana", "Cherry", "date", "ELEPHANT",
			"apple", "123", "!@#", "Zebra", nullptr
		};

		for (const auto& test_str : test_data) {
			strings.push_back(String(test_str));
		}
	}


	std::cout << "\nOriginal list (" << strings.size() << " strings):" << std::endl;
	for (const auto& str : strings) {
		std::cout << "  " << str.data() << std::endl;
	}

	// reverse lexicographical order
	std::sort(strings.begin(), strings.end(), [](const String& a, const String& b) {
		return case_insensitive_compare(b, a);
		});

	std::cout << "\nResult in reverse lexicographical order (case-insensitive):" << std::endl;
	for (const auto& str : strings) {
		std::cout << str.data() << std::endl;
	}

	return 0;
}