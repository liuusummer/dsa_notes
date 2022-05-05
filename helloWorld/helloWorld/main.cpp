
#include "Sales_data.h"
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// test
struct X {
	static int i;
	int j;
	explicit X(int value) :j(value) { cout << "一个int参数的构造函数\n"; }

	X() {
		++i;
		j = i;
		std::cout << "默认构造函数" << j << std::endl;
	}

	X(const X &) {
		++i;
		j = i;
		std::cout << "拷贝构造函数" << j << endl;
	}

	X &operator=(const X &) {
		++i;
		j = i;
		std::cout << "复制构造函数" << j << std::endl;
	}

	~X() {
		std::cout << "析构函数" << j << std::endl;
	}
};

int X::i = 0;

void f1(X x){}
void f2(X &x) {}

X f3() {
	return X();
}
X &f4(X &x) {
	return x;
}
X f5() {
	X x;
	return x;
}

class numbered {
public:
	numbered() :mysn(++sn) { cout << "默认构造函数\n"; }
	numbered(const numbered &n) :mysn(++sn){
		cout << "拷贝构造函数\n";
	}

	int mysn;
private:
	static int sn;
};
int numbered::sn = 0;
void f(numbered s) {
	cout << s.mysn << endl;
}

class Employee {
private:
	string name;
	unsigned id;
	static unsigned ID;
public:
	
	Employee() :id(++ID) {

	}
	explicit Employee(const string &s) :name(s), id(++ID) {

	}
	Employee(const Employee &e) : name(e.name), id(++ID) { cout << "拷贝构造\n"; }

	Employee &operator=(const Employee &e);
	string getName()const { return name; }
	unsigned getID()const { return id; }
};
unsigned Employee::ID = 0;
Employee &Employee::operator=(const Employee &e) {
	cout << "拷贝赋值运算符\n";
	name = e.name;
	//id = ++eid;  // keep the old id
	return *this;
}

// 函数对象类
struct  IfThenElse{
	using value_type = int;
	value_type operator()(bool condition, value_type t, value_type f)const {
		return condition ? t : f;
	}
};

class comp {
public:
	comp(int v) :value(v) {};
	bool operator()(int a) {
		return value == a;
	}
private:
	int value;
};

class StrRange {
public:
	StrRange(size_t l, size_t h) :low(l), high(h) {};
	bool operator()(const std::string&s) {
		return s.size() <= high && s.size() >= low;
	}

private:
	size_t low;
	size_t high;
};


int main() {
	//Sales_data  total;   // 保存当前求和结果的变量
	//if (read(cin, total)) {  // 读入第一笔交易
	//	Sales_data trans;     // 保存下一条交易数据的变量
	//	while (read(cin, trans)) {   // 读入剩下的交易
	//		if (trans.isbn() == total.isbn()) {
	//			total.combine(trans);
	//		}
	//		else {
	//			print(cout, total) << endl;
	//			total = trans;
	//		}
	//	}
	//	print(cout, total) << endl;
	//}
	//else {
	//	cerr << "No data?!" << endl;
	//}

	/*Sales_data item("99",1,1);
	print(cout, item);
	std::string null_book = "99";*/
	//  item.combine(null_book);
	// item.combine("99");
	// item.combine(string("99"));
	// item.combine(Sales_data("99",1,1));
	// item.combine(cin);
	// Sales_data item2 = null_book;
	// Sales_data item1(cin);
	// item.combine(static_cast<Sales_data>(cin));
	 /*item.combine(null_book);
	cout << endl;
	 print(cout, item);*/

	 /*vector<Sales_data> v;
	 v.push_back(Sales_data("ABC", 1, 3));
	 v.emplace_back("aA", 2, 3);
	 v.emplace_back(Sales_data("aa", 3, 3));
	 sort(v.begin(), v.end(), compareIsbn);

	 for (const auto &x : v) {
		 print(cout, x) << endl;
	 }

	 cout << int('a') << " " << int('A');*/

	 //using compareType = bool(*)(const Sales_data &, const Sales_data &);
	 //multiset<Sales_data, compareType> bookStore(compareIsbn);

	 //// multiset<Sales_data, compareType>::iterator it = bookStore.begin();
	 //bookStore.insert({ "c",1,1 });
	 //bookStore.insert({ "b",2,2 });
	 //bookStore.insert({ "a",3,3 });
	 //

	 ////vector<Sales_data> bookStore = { {"a",1,1},{"c",2,2},{"b",3,3} };
	 //
	 //for_each(bookStore.begin(), bookStore.end(),
	 //	bind(print, ref(cout), placeholders::_1));

	 /*set<int> s = { 1,2,3,5,6,7 };
	 auto it = s.find(4);
	 if (it != s.end()) {
		 cout << "found.\n";
	 }
	 else {
		 cout << "not found.\n";
	 }
	 auto lower = s.lower_bound(4);
	 auto upper = s.upper_bound(4);
	 if (lower == upper) {
		 cout << "get.\n";
	 }*/

	 //Sales_data s("xxx");
	 // Sales_data s2("xxxx");
	 // fcn(&s, s2);
	 //Sales_data s3("xxxxxxx");
	 //print(cout, s) << endl;
	 //print(cout, s2) << endl;
	 //print(cout, s3) << endl;

	 //std::cout << "\n----- X x1;\n";
	 // //X x1;
	 // //X x2 = x1;
	 //X x = X(1);
	 // X x(1);
	 //std::cout << "\n----- f1(x1);\n";
	 //f1(x1);

	 //std::cout << "\n----- f2(x1);\n";
	 //f2(x1);

	 //std::cout << "\n----- X x3 = f3();\n";
	 //X x3 = f3();

	 //std::cout << "\n----- f3();\n";
	 //f3();
	 //std::cout << "\n----- X x5 = f5();\n";
	 //X x5 = f5();
	 //std::cout << "\n----- f5();\n";
	 //f5();
	 //std::cout << "\n----- X x4 = f4(x1);\n";
	 //X x4 = f4(x1);
	 //std::cout << "\n----- f4(x1);\n";
	 //f4(x1);
	 //std::cout << "\n----- X *x2 = new X;\n";
	 //X *x2 = new X;
	 //std::cout << "\n----- std::vector<X> vx;\n";
	 //std::vector<X> vx;
	 //std::cout << "\n----- vx.push_back(x1);\n";
	 //vx.push_back(x1);
	 //std::cout << "\n----- vx.push_back(*x2);\n";
	 //vx.push_back(*x2);  // The vector is reallocate here.
	 //std::cout << "\n----- std::list<X> vl;\n";
	 //std::list<X> vl;
	 //std::cout << "\n----- vl.push_back(x1);\n";
	 //vl.push_back(x1);
	 //std::cout << "\n----- vl.push_back(*x2);\n";
	 //vl.push_back(*x2);  // The list does not need reallocate.
	 //std::cout << "\n----- delete x2;\n";
	 //delete x2;
	 //std::cout << "\n----- \n";


	 /*numbered a, b = a, c = b;
	 f(a);
	 f(b);
	 f(c);
	 numbered d;
	 f(d);*/




	 /*Employee e1;
	 std::cout << e1.getName() << " " << e1.getID() << std::endl;
	 Employee e2("Zhang San");
	 std::cout << e2.getName() << " " << e2.getID() << std::endl;
	 Employee e3 = e2;
	 std::cout << e3.getName() << " " << e3.getID() << std::endl;
	 e1 = e2;
	 std::cout << e1.getName() << " " << e1.getID() << std::endl;
	 std::cout << e2.getName() << " " << e2.getID() << std::endl;*/


	 /*int i;
	 std::cin >> i;
	 std::cout << IfThenElse()(i > 0, 1, -1) << std::endl;*/

	//std::vector<int> v{ 1,2,3,4,5 };
	////comp c; // error:不存在默认构造函数(因为定义了构造函数)
	//replace_if(v.begin(), v.end(), comp(3), 100);
	//for_each(v.begin(), v.end(), [](const int a) {std::cout << a << " "; });
	//


	
	
	for (size_t length = 1; length <= 10; length++) {
		std::ifstream fin("d:\\dsa_notes\\helloworld\\helloworld\\mapAndset\\test.txt");
		if (!fin.is_open()) {
			cerr << "error\n";
		}
		std::istream_iterator<std::string> iter(fin), eof;
		std::cout << "number of size = " << length << " : "
			<< count_if(iter, eof, StrRange(length, length)) << std::endl;
		fin.close();
	}
	




	return 0;
}
