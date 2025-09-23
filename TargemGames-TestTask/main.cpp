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

		strings.push_back(String("Apple"));
		strings.push_back(String("banana"));
		strings.push_back(String("Cherry"));
		strings.push_back(String("date"));
		strings.push_back(String("ELEPHANT"));
		strings.push_back(String("apple"));
		strings.push_back(String("123"));
		strings.push_back(String("!@#"));
		strings.push_back(String("Zebra"));
	}


	std::cout << "\nOriginal list (" << strings.size() << " strings):" << std::endl;
	for (const auto& str : strings) {
		std::cout << "  " << str.c_str() << std::endl;
	}

	// reverse lexicographical order
	std::sort(strings.begin(), strings.end(), [](const String& a, const String& b) {
		return case_insensitive_compare(b, a);
		});

	std::cout << "\nResult in reverse lexicographical order (case-insensitive):" << std::endl;
	for (const auto& str : strings) {
		std::cout << str.c_str() << std::endl;
	}

	return 0;
}