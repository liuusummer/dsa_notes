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
	std::size_t min_qty = 0;  // �����ۿ����ߵ���͹�����
	double discount = 0.0;     // ��С����ʾ���ۿ۶�
};
// ���캯��
Bulk_quote::Bulk_quote(const std::string &book, double p,
	std::size_t qty, double disc) :
	Quote(book, p), min_qty(qty), discount(disc) {
}
// ����ﵽ�˹����鼮��ĳ���������ֵ���Ϳ��������ۿۼ۸���
double Bulk_quote::net_price(std::size_t cnt) const{
	if (cnt > min_qty) {
		return cnt * (1 - discount) * price;
	}
	else {
		return cnt * price;
	}
}


// �������޵��ۿ۲���
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
			// ��������������ʱ�����ۿ�  ������� �����Ĳ�����ԭ������
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