#ifndef hashTable_h
#define hashTable_h

#include <iostream>
//#include "hash.h"   // K���Ǹ�����
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
	// ɢ�б���һά����table[]��ʾ��������pair<const K,E>*
	int search(const K &)const;
	pair<const K, E> **table;   // hash table ɢ�б�
	// hash<K> hash;    // ������Kӳ�䵽һ���Ǹ�����
	// int hash;
	int dSize;   // �ֵ������Ը���
	int divisor;    // ɢ�к�������
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
	// ����һ��������ַɢ�б� ���ҹؼ���ΪtheKey������
	// ���ƥ������Դ��ڣ���������λ���������������ɢ�б���
	// ���عؼ���ΪtheKey�����Կ��Բ����λ��
	// 
	// 
	// int i = (int)hash(theKey) % divisor;
	int i = theKey % divisor;  // ��ʼͰ
	int j = i;   // ����ʼͰ��ʼ
	do {
		if (table[j] == nullptr || table[j]->first == theKey) {
			return j;
		}
		j = (j + 1) % divisor;  // ��һ��Ͱ
	} while (j != i);   // �Ƿ񷵻ص���ʼͰ
	return j;   // ����
}

template <class K,class E>
pair<const K, E> *hashTable<K, E>::find(const K &theKey)const {
	// ����ƥ�����Ե�ָ��
	// ���ƥ�����Բ����ڣ�����NULL
	
	// ����ɢ�б�
	int b = search(theKey);
	// �ж�table[b]�Ƿ���ƥ������
	if (table[b] == nullptr || table[b]->first != theKey) {
		return nullptr;
	}
	return table[b];   // �ҵ�ƥ������
}

template <class K,class E>
void hashTable<K, E>::insert(const pair<const K, E> &thePair) {
	// ������thePair�����ֵ䣬�����ڹؼ�����ͬ�����ԣ��򸲸�
	// ���������׳��쳣

	// ����ɢ�б�����ƥ�������
	int b = search(thePair.first);
	// ���ƥ��������Ƿ����
	if (table[b] == nullptr) {
		// û��ƥ�������  ���ұ�δ��
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else {
		// ����Ƿ����ظ��Ĺؼ������� ��  �Ƿ����
		if (table[b]->first == thePair.first) {
			// ���ظ��Ĺؼ������ԣ��޸�table[b]->second
			table[b]->second = thePair.second;
		}
		else {
			throw hashTableFull();   // ����
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