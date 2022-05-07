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
	virtual ~Quote() = default;   // �������������ж�̬��
private:
	std::string bookNo;   // �鼮��ISBN���
protected:
	double price = 0.0;   // ������ͨ״̬�²����۵ļ۸�
};
// �������
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

// ����ʵ��Bulk_quote  �̳�Disc_quote����ֱ�Ӽ̳�Quote
// ��ͬһ�鼮������������ĳ��ֵʱ�����ۿ�
class Bulk_quote :public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&book,double p,
		std::size_t qty,double disc):
		Disc_quote(book,p,qty,disc){ }
	double net_price(std::size_t)const override;
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
#endif