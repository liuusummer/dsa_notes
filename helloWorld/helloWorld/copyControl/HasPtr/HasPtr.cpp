#include "HasPtr.h"
using namespace std;
int main() {
	HasPtr hp1 = "World";
	HasPtr hp2 = hp1;
	HasPtr hp3;
	hp3 = hp1;
	// hp1.set("Hello");

	std::cout << hp1.get() << std::endl;
	std::cout << hp2.get() << std::endl;
	std::cout << hp3.get() << std::endl;

	//hp1 = hp1;
	std::cout << "After `hp1 = hp1`: " << hp1.get() << std::endl;


	return 0;
}