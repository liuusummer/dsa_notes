#ifndef Quote_h_
#define Quote_h_
#include <iostream>
#include <string>

class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) :
		bookNo(book), price(sales_price) {
	}
	std::string isbn()const { return bookNo; }

	// 返回给定数量的书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算方法
	virtual double net_price(std::size_t n)const {
		return n * price;
	}

	// debug  显示每一个数据成员
	virtual void debug()const {
		std::cout << "bookNo: " << bookNo << ",price: " << price << std::endl;
	}
	virtual ~Quote() = default;   // 对析构函数进行动态绑定
private:
	std::string bookNo;   // 书籍的ISBN编号
protected:
	double price = 0.0;   // 代表普通状态下不打折的价格
};

class Bulk_quote :public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &, double, std::size_t, double);
	double net_price(std::size_t)const override;
	void debug()const override {
		std::cout << "min_qty: " << min_qty <<
			",discount: " << discount << std::endl;
	}
	void printTest()const { std::cout << price; }   // error
private:
	std::size_t min_qty = 0;  // 适用折扣政策的最低购买量
	double discount = 0.0;     // 以小数表示的折扣额
};
// 构造函数
Bulk_quote::Bulk_quote(const std::string &book, double p,
	std::size_t qty, double disc) :
	Quote(book, p), min_qty(qty), discount(disc) {
}
// 如果达到了购买书籍的某个最低限量值，就可以享受折扣价格了
double Bulk_quote::net_price(std::size_t cnt) const{
	if (cnt > min_qty) {
		return cnt * (1 - discount) * price;
	}
	else {
		return cnt * price;
	}
}


// 数量受限的折扣策略
class Limit_quote :public Quote {
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double p,
		std::size_t n, double dis) 
		:Quote(book, p), max_qty(n), discount(dis) {
	}
	double net_price(std::size_t cnt)const override {
		if (cnt <= max_qty) {
			return cnt * (1 - discount) * price;
		}
		else {
			// 数量不超过限量时享受折扣  如果超出 超出的部分以原价销售
			return max_qty * price * (1 - discount) + (cnt - max_qty) * price;
		}
	}

	void debug()const override {
		std::cout << "max_qty: " << max_qty
			<< ",discount: " << discount << std::endl;
	}

private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};
#endif