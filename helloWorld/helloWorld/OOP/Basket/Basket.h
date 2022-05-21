#ifndef Basket_h_
#define Basket_h_
#include "D:\\dsa_notes\\helloWorld\\helloWorld\\OOP\\Quote.h"
#include <set>
#include <memory>
class Basket {
public:
	// Basket使用合成的默认构造函数和拷贝控制成员
	/*void add_item(const std::shared<Quote> &sale) {
		item.insert(sale);
	}*/
	// 拷贝给定的对象
	void add_item(const Quote &sale) {
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}
	// 移动给定的对象
	void add_item(Quote &&sale) {
		items.insert(
			std::shared_ptr<Quote>(std::move(sale.clone())));
	}


	// 负责将购物篮的内容逐项打印成清单然后返回所有物品的总价
	double total_receipt(std::ostream &)const;
private:
	// 该函数用于比较shared_ptr ,multiset成员会用到它
	static bool compare(const std::shared_ptr<Quote> &lhs,
		const std::shared_ptr<Quote> &rhs) {
		return lhs->isbn() < rhs->isbn();
	}
	// multiset保存多个报价  按照compare成员排序
	std::multiset<std::shared_ptr<Quote>, decltype(compare) *>
		items{ compare };
};
double Basket::total_receipt(std::ostream &os)const {
	double sum = 0.0;   // 保存实时计算出的总价格
	// iter 指向ISBN相同的一批元素中的第一个
	// upper_bound 返回一个迭代器 该迭代器指向这批元素的尾后位置
	for (auto iter = items.cbegin();
		iter != items.cend();
		iter = items.upper_bound(*iter)) {
		// 打印该书籍对应的项目
		sum += print_total(os, **iter, items.count(*iter));
	}
	os << "Total Sale: " << sum << std::endl;
	return sum;
}


#endif