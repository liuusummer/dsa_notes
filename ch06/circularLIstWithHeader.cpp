#include <iostream>
#include "circularListWithHeader.h"

using std::endl;
using std::cout;

int main() {
	// error
	circularListWithHeader<int> x;
	cout << x << endl;


	return 0;
}