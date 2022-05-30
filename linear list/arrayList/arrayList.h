#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#include "linearList.h"
#include <iostream>
#include "D:\\dsa\\myExceptions.h"
#include "D:\\dsa\\changeLength1D.h"
#include <string>
#include <sstream>
#include <algorithm>
/*
* ���������linearList��������arrayList
* arrayList��һ�������࣬����ʵ�ֳ�����linearList�����з�����������linearListû�������ķ���
* ����capacity������������element��ǰ�ĳ���
* ����checkIndexҪȷ��һ��Ԫ���ڷ�Χ0��listSize-1�ڵ�����
*/

template <typename T> class arrayList;
// operator << 
template<typename T>
std::ostream &operator<<(std::ostream &, const arrayList<T> &);


template<typename T>
class arrayList : public linearList<T> {
public:
	// constructor  copy constructor destructor
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT����
	virtual bool empty()const override{ return listSize == 0; }
	virtual int size()const override{ return listSize; }
	virtual T &get(int theIndex)const override;
	virtual int indexOf(const T &theElement)const override;
	virtual void erase(int theIndex) override;
	virtual void insert(int theIndex, const T &theElement) override;
	virtual void output(std::ostream &out)const override;

	// ��������
	int capacity()const { return arrayLength; }

protected:
	void checkIndex(int theIndex)const;
	// ������theIndex��Ч�����׳��쳣
	T *element;    // �洢���Ա�Ԫ�ص�һά����
	int arrayLength;  // һά���������
	int listSize;     // ���Ա��Ԫ�ظ���
};


#endif
