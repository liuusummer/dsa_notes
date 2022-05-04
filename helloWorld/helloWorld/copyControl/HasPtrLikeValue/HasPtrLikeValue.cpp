#include <iostream>
#include <vector>
#include <algorithm>
#include "HasPtr.h"

void testHasPtrVec(std::vector<HasPtr> &v) {
	std::cout << "\nBefore sort " << v.size() << " element:\n";
	for (const auto &e : v) {
		std::cout << e.get() << std::endl;
	}
	std::cout << "\nSorting:\n";
	std::sort(v.begin(), v.end());
	std::cout << "\nAfter sort:\n";
	for (const auto &e : v) {
		std::cout << e.get() << std::endl;
	}
}
int main() {
	/*HasPtr hp1 = "World";
	HasPtr hp2 = hp1;
	HasPtr hp3;
	hp3 = hp1;
	hp1.set("Hello");

	std::cout << hp1.get() << std::endl;
	std::cout << hp2.get() << std::endl;
	std::cout << hp3.get() << std::endl;

	hp1 = hp1;
	std::cout << "After `hp1 = hp1`: " << hp1.get() << std::endl;

	swap(hp1, hp2);
	std::cout << hp1.get() << std::endl;
	std::cout << hp2.get() << std::endl;

	swap(hp1, hp1);
	std::cout << hp1.get() << std::endl;*/


	std::vector<HasPtr> v{ "Hello", "World", "P", "Q", "R", "S", "T", "U",
	  "ABC", "DEF", "AB", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
	  "ABC", "DEF", "AB", "C", "D", "E", "J", "K", "L", "M", "N" };
	testHasPtrVec(v);
	// Note that if the total count of elements in vector is small (e.g. less
	// than 32 in VS2015), then no swap will be made when sorting.
	std::vector<HasPtr> v2{ "Hello", "World", "P", "Q", "R", "S", "T", "U",
		"ABC", "DEF", "AB", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
		"ABC", "DEF", "AB", "C", "D", "E", "J", "K", "L", "M", "N", "O" };
	testHasPtrVec(v2);




	return 0;



	
}
