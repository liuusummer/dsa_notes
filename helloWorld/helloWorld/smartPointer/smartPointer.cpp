#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "StrBlob.h"

using namespace std;

shared_ptr<vector<int>> alloc_vector() {
	return make_shared<vector<int>>();
}

void assign_vector(shared_ptr<vector<int>> p) {
	int i;
	while (cin >> i) {
		p->push_back(i);
	}
}
void print_vector(shared_ptr<vector<int>> p) {
	for (auto x : *p) {
		cout << x << " ";
	}
}
void process(shared_ptr<int> ptr) {
	cout << *ptr;
	cout << " ptr.use_count() = " << ptr.use_count() << endl;
}

int main() {

	/*auto p = alloc_vector();
	assign_vector(p);
	print_vector(p);*/
	// delete p;


	// return 0;

	/*StrBlob b1;
	{
		StrBlob b2 = { "a","an","the" };
		b1 = b2;
		b2.push_back("about");
	}*/
	//b1.print();
	// b2.print();
	// StrBlob b1;
	// b1 = b2;

	//int *x(new int(42));
	//shared_ptr<int> p(new int(43));
	//// process(x);
	//cout << p.use_count() << " ";
	//
	//process(shared_ptr<int>(p.get()));
	//cout << p.use_count() << " ";
	//

	/*shared_ptr<int> p(new int(5));
	weak_ptr<int> q(p);
	cout << p.use_count();

	if (shared_ptr<int> np = q.lock()) {
		cout << *np << endl;
		cout << p.use_count();
	}

	cout <<endl<<  p.use_count();*/


	/*ifstream fin("D:\\dsa_notes\\helloWorld\\helloWorld\\smartPointer\\book.txt");
	if (!fin.is_open()) {
		cerr << "error.";
	}
	StrBlob text;
	string line;
	while (getline(fin, line)) {
		text.push_back(line);
	}

	StrBlobPtr p = text.begin();
	for (StrBlob::size_type pos = 0; pos != text.size(); ++pos, p.incr()) {
		std::cout << pos + 1 << " : " << p.deref() << endl;
	}*/

	allocator<string> a;
	constexpr size_t n = 10;
	
	auto const p = a.allocate(n);
	auto q = p;
	string s;
	while (cin >> s && q != p + n) {
		a.construct(q++, s);
	}
	
	const size_t sz = q - p; // size
	for (auto pos = p; pos != p + sz; pos++) {
		cout << *pos << endl;
	}
	while (q != p) {
		a.destroy(--q);
	}
	a.deallocate(p, n);

	return 0;
}