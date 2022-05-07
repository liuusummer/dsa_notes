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
	virtual std::ostream &debug(std::ostream &os)const{
		os << "Quote::bookNo " << bookNo << " Quote::price " << price;
		return os;
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
// 抽象基类
class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string&book,double price,
		std::size_t qty,double disc):
		Quote(book,price),
		quantity(qty),discount(disc){ }
	double net_price(std::size_t) const = 0;

	std::ostream &debug(std::ostream &os)const override{
		Quote::debug(os) << " Disc_quote::quantity " << quantity
			<< " Disc_quote::discount " << discount;
		return os;
	}

protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

// 重新实现Bulk_quote  继承Disc_quote而非直接继承Quote
// 当同一书籍的销售量超过某个值时启用折扣
class Bulk_quote :public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&book,double p,
		std::size_t qty,double disc):
		Disc_quote(book,p,qty,disc){ }
	double net_price(std::size_t)const override;
};

// 如果达到了购买书籍的某个最低限量值，就可以享受折扣价格了
double Bulk_quote::net_price(std::size_t cnt) const{
	if (cnt >= quantity) {
		return cnt * (1 - discount) * price;
	}
	else {
		return cnt * price;
	}
}


// 数量受限的折扣策略
class Limit_quote :public Disc_quote {
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double p,
		std::size_t n, double dis) 
		:Disc_quote(book, p,n,dis) {
	}
	double net_price(std::size_t cnt)const override {
		if (cnt <= quantity) {
			return cnt * (1 - discount) * price;
		}
		else {
			// 数量不超过限量时享受折扣  如果超出 超出的部分以原价销售
			return quantity * price * (1 - discount) + (cnt - quantity) * price;
		}
	}
};
#endif