#include "Quote.h"
#include <iostream>
using namespace std;

double print_total(ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due:"
		<< ret << std::endl;
	return ret;
}
int main() {

	Quote basic("abc", 5.5);
	Bulk_quote bulk("abc", 5.5, 10, 0.2);
	Limit_quote limit("abc", 5.5, 30, 0.3);
	//print_total(std::cout, basic, 20);
	//print_total(std::cout, bulk, 20);

	

	print_total(std::cout, basic, 20);
	print_total(std::cout, bulk, 20);
	print_total(std::cout, limit, 20);

	basic.debug(std::cout) << std::endl;
	bulk.debug(std::cout) << std::endl;
	limit.debug(std::cout) << std::endl;




	return 0;


}