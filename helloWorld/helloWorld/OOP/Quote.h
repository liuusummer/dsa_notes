#ifndef Quote_h_
#define Quote_h_
#include <iostream>
#include <string>

class Quote {
	friend bool operator!=(const Quote &lhs, const Quote &rhs);
public:
	
	Quote() { std::cout << "default constructing Quote\n"; }
	Quote(const std::string &book, double sales_price) :
		bookNo(book), price(sales_price) {
		std::cout << "Quote:constructor taking 2 parameters\n";
	}
	// copy constructor
	Quote(const Quote &q):bookNo(q.bookNo),price(q.price) {
		std::cout << "Quote: copy constructing\n";
	}
	// move constructor
	Quote(Quote &&q)noexcept :
		bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
		std::cout << "Quote: move constructing\n";
	}
	// copy =
	Quote &operator=(const Quote &rhs) {
		if (*this != rhs) {
			bookNo = rhs.bookNo;
			price = rhs.price;
		}
		std::cout << "Quote: copy =() \n";
		return *this;
	}
	// move =
	Quote& operator=(Quote &&rhs) noexcept{
		if (*this != rhs) {
			bookNo = std::move(rhs.bookNo);
			price = std::move(rhs.price);
		}
		std::cout << "Quote: move =!!!!!!!!! \n";
		return *this;
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

	// 该虚函数返回当前对象的一份动态分配的拷贝
	virtual Quote *clone()const & { return new Quote(*this); }
	virtual Quote *clone() && 
		{ return new Quote(std::move(*this)); }


	virtual ~Quote() {
		std::cout << "destructing Quote\n";
	}// 对析构函数进行动态绑定
private:
	std::string bookNo;   // 书籍的ISBN编号
protected:
	double price = 10.0;   // 代表普通状态下不打折的价格
};

inline bool operator!=(const Quote &lhs, const Quote &rhs) {
	return lhs.bookNo != rhs.bookNo
		&&
		lhs.price != rhs.price;
}


// 抽象基类
class Disc_quote :public Quote {
	friend bool operator!=(const Disc_quote &lhs, const Disc_quote &rhs);
public:
	Disc_quote() { 
		std::cout << "default constructing Disc_quote\n"; }
	Disc_quote(const std::string&book,double price,
		std::size_t qty,double disc):
		Quote(book,price),
		quantity(qty),discount(disc){ 
		std::cout << "Disc_quote : constructor taking 4 parameters.\n";
	}

	// copy constructor
	Disc_quote(const Disc_quote &dq) :
		Quote(dq), quantity(dq.quantity), discount(dq.discount) {
		std::cout << "Disc_quote : copy constructor.\n";
	}

	// move constructor
	Disc_quote(Disc_quote &&dq) noexcept :
		Quote(std::move(dq)), quantity(std::move(dq.quantity)), discount(std::move(dq.discount)) {
		std::cout << "Disc_quote : move constructor.\n";
	}

	// copy =()
	Disc_quote &operator =(const Disc_quote &rhs) {
		Quote::operator =(rhs);
		this->quantity = rhs.quantity;
		this->discount = rhs.discount;

		std::cout << "Disc_quote : copy =()\n";

		return *this;
	}

	// move =()
	Disc_quote &operator =(Disc_quote &&rhs) noexcept {
		if (*this != rhs) {
			Quote::operator =(std::move(rhs));
			this->quantity = std::move(rhs.quantity);
			this->discount = std::move(rhs.discount);
		}
		std::cout << "Disc_quote : move =()\n";

		return *this;
	}





	virtual double net_price(std::size_t) const override = 0;

	std::ostream &debug(std::ostream &os)const override{
		Quote::debug(os) << " Disc_quote::quantity " << quantity
			<< " Disc_quote::discount " << discount;
		return os;
	}

	~Disc_quote() {
		std::cout << "destructing Disc_quote.\n";
	}


protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};

bool inline
operator !=(const Disc_quote &lhs, const Disc_quote &rhs) {
	return Quote(lhs) != Quote(rhs)
		&&
		lhs.quantity != rhs.quantity
		&&
		lhs.discount != rhs.discount;
}


// 重新实现Bulk_quote  继承Disc_quote而非直接继承Quote
// 当同一书籍的销售量超过某个值时启用折扣
class Bulk_quote :public Disc_quote {
public:
	Bulk_quote() {
		std::cout << "default constructing Bulk_quote\n";
	}
	Bulk_quote(const std::string&book,double p,
		std::size_t qty,double disc):
		Disc_quote(book,p,qty,disc){
		std::cout << "Bulk_quote : constructor taking 4 parameters\n";
	}

	// copy constructor
	Bulk_quote(const Bulk_quote &bq) : Disc_quote(bq) {
		std::cout << "Bulk_quote : copy constructor\n";
	}

	// move constructor
	Bulk_quote(Bulk_quote &&bq)noexcept : Disc_quote(std::move(bq)){
		std::cout << "Bulk_quote : move constructor\n";
	}

	// copy =()
	Bulk_quote &operator =(const Bulk_quote &rhs) {
		Disc_quote::operator =(rhs);
		std::cout << "Bulk_quote : copy =()\n";

		return *this;
	}


	// move =()
	Bulk_quote &operator =(Bulk_quote &&rhs) noexcept {
		Disc_quote::operator =(std::move(rhs));
		std::cout << "Bulk_quote : move =()\n";

		return *this;
	}

	double net_price(std::size_t)const override;
	~Bulk_quote() override {
		std::cout << "destructing Bulk_quote\n";
	}

	Bulk_quote *clone()const & { return new Bulk_quote(*this); }
	Bulk_quote *clone() && {
		return new Bulk_quote(std::move(*this));
	}

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

// print_total
double print_total(std::ostream &os, const Quote &item, size_t n) {
	// 根据传入item的形参的对象调用Quote::net_price
	// 或者Bulk_quote::net_price
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() // 调用Quote::isbn
		<< " # sold: " << n << " total due: " 
		<< ret << std::endl;
	return ret;
}

#endif