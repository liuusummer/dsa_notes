#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <iterator>
using namespace std;
void elimDups(vector<string> &words) {
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

bool check_size(const string &s, string::size_type sz) {
	return s.size() >= sz;
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	//auto wc = find_if(words.begin(), words.end(),
	//	[sz](const string &s)->bool {return s.size() >= sz; });

	auto wc = find_if(words.begin(), words.end(),
		bind(check_size, placeholders::_1, sz));
	auto count = words.end() - wc;
	
	for_each(words.begin(), words.end(),
		[](const string &s) {cout << s << " "; });
	
	
	cout << endl;
}
int main() {

	vector<int> foo;
	
	// Á÷µü´úÆ÷
	istream_iterator<int> it(cin), eof;
	vector<int> vi(it, eof);


	for_each(vi.begin(), vi.end(),
		[](int a) {cout << a << " "; });
	auto iter = vi.rbegin();

	return 0;
}