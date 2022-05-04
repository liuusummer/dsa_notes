#ifndef hashTable_h
#define hashTable_h

#include <iostream>
//#include "hash.h"   // K到非负整数
#include "D:\\dsa_notes\\myExceptions.h"
using namespace std;
template <class K,class E>
class hashTable {
public:
	hashTable(int theDivisor = 11);
	~hashTable() { delete[]table; }

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E> *find(const K &)const;
	void insert(const pair<const K, E> &);
	void output(ostream &out)const;
protected:
	// 散列表用一维数组table[]表示，类型是pair<const K,E>*
	int search(const K &)const;
	pair<const K, E> **table;   // hash table 散列表
	// hash<K> hash;    // 把类型K映射到一个非负整数
	// int hash;
	int dSize;   // 字典中数对个数
	int divisor;    // 散列函数除数
};

template <class K,class E>
hashTable<K,E>::hashTable(int theDivisor) {
	divisor = theDivisor;
	dSize = 0;

	// allocate and initialize table array
	table = new pair<const K, E> *[theDivisor];
	for (int i = 0; i < theDivisor; i++) {
		table[i] = nullptr;
	}
}

template <class K,class E>
int hashTable<K, E>::search(const K &theKey)const {
	// 搜索一个公开地址散列表 查找关键字为theKey的数对
	// 如果匹配的数对存在，返回它的位置索引，否则，如果散列表不满
	// 返回关键字为theKey的数对可以插入的位置
	// 
	// 
	// int i = (int)hash(theKey) % divisor;
	int i = theKey % divisor;  // 起始桶
	int j = i;   // 从起始桶开始
	do {
		if (table[j] == nullptr || table[j]->first == theKey) {
			return j;
		}
		j = (j + 1) % divisor;  // 下一个桶
	} while (j != i);   // 是否返回到起始桶
	return j;   // 表满
}

template <class K,class E>
pair<const K, E> *hashTable<K, E>::find(const K &theKey)const {
	// 返回匹配数对的指针
	// 如果匹配数对不存在，返回NULL
	
	// 搜索散列表
	int b = search(theKey);
	// 判断table[b]是否是匹配数对
	if (table[b] == nullptr || table[b]->first != theKey) {
		return nullptr;
	}
	return table[b];   // 找到匹配数对
}

template <class K,class E>
void hashTable<K, E>::insert(const pair<const K, E> &thePair) {
	// 把数对thePair插入字典，若存在关键字相同的数对，则覆盖
	// 若表满则抛出异常

	// 搜索散列表，查找匹配的数对
	int b = search(thePair.first);
	// 检查匹配的数对是否存在
	if (table[b] == nullptr) {
		// 没有匹配的数对  而且表未满
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else {
		// 检查是否有重复的关键字数对 或  是否表满
		if (table[b]->first == thePair.first) {
			// 有重复的关键字数对，修改table[b]->second
			table[b]->second = thePair.second;
		}
		else {
			throw hashTableFull();   // 表满
		}
	}
}


template<class K, class E>
void hashTable<K, E>::output(ostream &out) const {// Insert the hash table into the stream out.
	for (int i = 0; i < divisor; i++)
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " "
			<< table[i]->second << endl;
}

// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const hashTable<K, E> &x) {
	x.output(out); return out;
}

#endif