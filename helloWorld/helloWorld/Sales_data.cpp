#include "Sales_data.h"

Sales_data::Sales_data(std::istream &is) {
	std::cout << "使用了cin参数的构造函数";
	read(is, *this);
}
Sales_data::Sales_data(const Sales_data &orig)
	:bookNo(orig.bookNo),
	units_sold(orig.units_sold),
	revenue(orig.revenue){
	std::cout << "copy constructor\n";
}
Sales_data &Sales_data::operator=(const Sales_data &rhs) {
	bookNo = rhs.bookNo;
	units_sold = rhs.units_sold;
	revenue = rhs.revenue;
	std::cout << "copy assignment operator\n";
	return *this;
}
double Sales_data::avg_price()const {
	if (units_sold) {
		return revenue / units_sold;
	}
	else {
		return 0;
	}
}

//Sales_data &Sales_data::combine(const Sales_data &rhs) {
//	std::cout << "const 版本" << std::endl;
//	units_sold += rhs.units_sold;
//	revenue += rhs.revenue;
//	return *this;
//}

Sales_data &Sales_data::combine(Sales_data rhs) {
	std::cout << "非引用 版本" << std::endl;
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

std::istream &read(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = item.units_sold * price;
	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

bool compareIsbn(const Sales_data &s1, const Sales_data &s2) {
	return s1.isbn() < s2.isbn();
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

std::istream &operator>>(std::istream &is,Sales_data &item) {
	double price;
	is >> item.bookNo >> item.units_sold >> price;
	if (is) {
		item.revenue = item.units_sold * price;
	}
	else {
		item = Sales_data();
	}
	return is;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}