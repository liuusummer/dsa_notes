#ifndef Basket_h_
#define Basket_h_
#include "D:\\dsa_notes\\helloWorld\\helloWorld\\OOP\\Quote.h"
#include <set>
#include <memory>
class Basket {
public:
	// Basketʹ�úϳɵ�Ĭ�Ϲ��캯���Ϳ������Ƴ�Ա
	/*void add_item(const std::shared<Quote> &sale) {
		item.insert(sale);
	}*/
	// ���������Ķ���
	void add_item(const Quote &sale) {
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}
	// �ƶ������Ķ���
	void add_item(Quote &&sale) {
		items.insert(
			std::shared_ptr<Quote>(std::move(sale.clone())));
	}


	// ���𽫹����������������ӡ���嵥Ȼ�󷵻�������Ʒ���ܼ�
	double total_receipt(std::ostream &)const;
private:
	// �ú������ڱȽ�shared_ptr ,multiset��Ա���õ���
	static bool compare(const std::shared_ptr<Quote> &lhs,
		const std::shared_ptr<Quote> &rhs) {
		return lhs->isbn() < rhs->isbn();
	}
	// multiset����������  ����compare��Ա����
	std::multiset<std::shared_ptr<Quote>, decltype(compare) *>
		items{ compare };
};
double Basket::total_receipt(std::ostream &os)const {
	double sum = 0.0;   // ����ʵʱ��������ܼ۸�
	// iter ָ��ISBN��ͬ��һ��Ԫ���еĵ�һ��
	// upper_bound ����һ�������� �õ�����ָ������Ԫ�ص�β��λ��
	for (auto iter = items.cbegin();
		iter != items.cend();
		iter = items.upper_bound(*iter)) {
		// ��ӡ���鼮��Ӧ����Ŀ
		sum += print_total(os, **iter, items.count(*iter));
	}
	os << "Total Sale: " << sum << std::endl;
	return sum;
}


#endif