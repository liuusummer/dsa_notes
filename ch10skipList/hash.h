/*
将关键字K转换成一个非负整数
// 有点问题  没有使用 

*/
#ifndef Hash_
#define Hash_

#include <iostream>
#include <string>

using namespace std;

// template <class K> class hash;

//template<>
//class hash<string> {
//public:
//	size_t operator()(const string theKey)const {
//		// theKey转换成一个非负整数
//		unsigned long hashValue = 0;
//		int length = (int)theKey.length();
//		for (int i = 0; i < length; i++) {
//			hashValue = 5 * hashValue + theKey.at(i);
//		}
//		return size_t(hashValue);
//	}
//};

class hash{
public:
	size_t operator()(const int theKey) const {
		return size_t(theKey);
	}
};

//template<>
//class hash<long> {
//public:
//	size_t operator()(const long theKey) const {
//		return size_t(theKey);
//	}
//};


#endif