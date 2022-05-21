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

	// ���ظ����������鼮�������ܶ�
	// �����ฺ���д��ʹ�ò�ͬ���ۿۼ��㷽��
	virtual double net_price(std::size_t n)const {
		return n * price;
	}
	virtual std::ostream &debug(std::ostream &os)const{
		os << "Quote::bookNo " << bookNo << " Quote::price " << price;
		return os;
	}

	// debug  ��ʾÿһ�����ݳ�Ա
	virtual void debug()const {
		std::cout << "bookNo: " << bookNo << ",price: " << price << std::endl;
	}

	// ���麯�����ص�ǰ�����һ�ݶ�̬����Ŀ���
	virtual Quote *clone()const & { return new Quote(*this); }
	virtual Quote *clone() && 
		{ return new Quote(std::move(*this)); }


	virtual ~Quote() {
		std::cout << "destructing Quote\n";
	}// �������������ж�̬��
private:
	std::string bookNo;   // �鼮��ISBN���
protected:
	double price = 10.0;   // ������ͨ״̬�²����۵ļ۸�
};

inline bool operator!=(const Quote &lhs, const Quote &rhs) {
	return lhs.bookNo != rhs.bookNo
		&&
		lhs.price != rhs.price;
}


// �������
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


// ����ʵ��Bulk_quote  �̳�Disc_quote����ֱ�Ӽ̳�Quote
// ��ͬһ�鼮������������ĳ��ֵʱ�����ۿ�
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

// ����ﵽ�˹����鼮��ĳ���������ֵ���Ϳ��������ۿۼ۸���
double Bulk_quote::net_price(std::size_t cnt) const{
	if (cnt >= quantity) {
		return cnt * (1 - discount) * price;
	}
	else {
		return cnt * price;
	}
}


// �������޵��ۿ۲���
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
			// ��������������ʱ�����ۿ�  ������� �����Ĳ�����ԭ������
			return quantity * price * (1 - discount) + (cnt - quantity) * price;
		}
	}
};

// print_total
double print_total(std::ostream &os, const Quote &item, size_t n) {
	// ���ݴ���item���βεĶ������Quote::net_price
	// ����Bulk_quote::net_price
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() // ����Quote::isbn
		<< " # sold: " << n << " total due: " 
		<< ret << std::endl;
	return ret;
}

#endif