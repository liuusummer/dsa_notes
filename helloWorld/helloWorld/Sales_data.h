// helloWorld.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef Sales_data_
#define Sales_data_
#include <iostream>
#include <string>

class Sales_data {

	friend Sales_data add(const Sales_data &, const Sales_data &);
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);

	// operator>>
	friend std::istream &operator>>(std::istream &, Sales_data &);
	// operator <<
	friend std::ostream &operator<<(std::ostream &, const Sales_data &);
	// operator +
	friend Sales_data operator+(const Sales_data &, const Sales_data &);
public:
	Sales_data &operator+=(const Sales_data &);
	// 四个构造函数
	Sales_data() = default;
	explicit Sales_data(const std::string &s):bookNo(s){}
	Sales_data(const std::string &s,unsigned n ,double p)
		:bookNo(s),units_sold(n),revenue(n*p){ }
	explicit Sales_data(std::istream &is);
	//copy constructor
	Sales_data(const Sales_data &);
	// copy assignment operator
	Sales_data &operator=(const Sales_data &);
	// destructor
	~Sales_data() {
		std::cout << "destructor\n";
	}
	
	std::string isbn()const{ return bookNo; }
	// Sales_data &combine(const Sales_data &);
	Sales_data &combine(Sales_data);

	

private:
	double avg_price()const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0;
};
// 非成员接口函数 add read print
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);

// compareIsbn
bool compareIsbn(const Sales_data &, const Sales_data &);
// operator>>
std::istream &operator>>(std::istream &, Sales_data &);
// operator <<
std::ostream &operator<<(std::ostream &, const Sales_data &);
// operator +
Sales_data operator+(const Sales_data &, const Sales_data &);

#endif
