#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_


/*
* ���������linearList��������arrayList
* arrayList��һ�������࣬����ʵ�ֳ�����linearList�����з�����������linearListû�������ķ���
* ����capacity������������element��ǰ�ĳ���
* ����checkIndexҪȷ��һ��Ԫ���ڷ�Χ0��listSize-1�ڵ�����
*/
#include <iostream>
#include "D:\\dsa_notes\\myExceptions.h"
#include "linearList.h"
#include "D:\\dsa_notes\\changeLength1D.h"
#include <string>
#include <sstream>
#include <algorithm>

template<class T>
class arrayList : public linearList<T> {
public:
	// ���캯�����������캯������������
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT����
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

	// ��������
	int capacity()const { return arrayLength; }
	
	//// ��arrayList��һ��������
	//class iterator;
	//iterator begin() { return iterator(element); }
	//iterator end() { return iterator(element + listSize); }

	//class iteraotr {
	//public:
	//	// ��typedefʵ��˫�������
	//	typedef bidirectional_iterator_tag iterator_category;
	//	typedef T value_type;
	//	typedef ptrdiff_t difference_type;
	//	typedef T *pointer;
	//	typedef T &reference;

	//	// ���캯��
	//	iterator(T *thePosition = 0) { position = thePosition; }

	//	// �����ò�����
	//	T &operator*()const { return *position; }
	//	T *operator->()const { return &*position; }

	//	// ��������ֵ����
	//	iterator &operator++() {   // ǰ��
	//		++position; return *this;
	//	}
	//	iterator operator++(int) {   // ���
	//		iterator old = *this;
	//		++position;
	//		return old;
	//	}

	//	// ��������ֵ����
	//	iterator &operator--() {
	//		--position; return *this;
	//	}
	//	iterator operator--(int) {
	//		iterator old = *this;
	//		--postion;
	//		return old;
	//	}
	//	// �����Ƿ����
	//	bool operator!=(const iterator right)const {
	//		return position != right.position;
	//	}
	//	bool operator==(const iterator right)const {
	//		return position == right.position;
	//	}
	//protected:
	//	T *position;   // ָ���Ԫ�ص�ָ��
	//};
protected:
	void checkIndex(int theIndex)const;
	// ������theIndex��Ч�����׳��쳣
	T *element;    // �洢���Ա�Ԫ�ص�һά����
	int arrayLength;  // һά���������
	int listSize;     // ���Ա��Ԫ�ظ���
};

// ���캯���Ϳ������캯��
template <class T>
arrayList<T>::arrayList(int initialCapacity) { // ���캯��
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial Capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {   // �������캯��
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex)const {   // ȷ������theIndex��0��listSize-1֮��
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}
template <class T>
T &arrayList<T>::get(int theIndex)const {  // ����������theIndex��Ԫ��
	// ����Ԫ�ز����ڣ����׳��쳣
	checkIndex(theIndex);
	return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement)const {
	// ����Ԫ��theElement��һ�γ���ʱ������
	// ����Ԫ�ز����ڣ��򷵻�-1

	// ����Ԫ��theElement
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	// ȷ��Ԫ���Ƿ��ҵ�
	if (theIndex == listSize) {  // û�ҵ�
		return -1;
	}
	else {
		return theIndex;
	}
}
template <class T>
void arrayList<T>::erase(int theIndex) {  // ɾ������ΪtheIndex��Ԫ��
	// ���Ԫ�ز����ڣ����׳��쳣
	checkIndex(theIndex);
	// ȷ������Ч�������ƶ�����������theIndex��Ԫ��
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	// listSize��ֵ-1
	element[--listSize].~T();   // ����ԭ�������һ��Ԫ��
}
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) { // ��theIndexλ�ò���ֵtheElement
	if (theIndex<0 || theIndex>listSize) {
		// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
	// ��Ч������ȷ�������Ƿ�����
	if (listSize == arrayLength) {
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// ��Ԫ�������ƶ�һ��λ��
	/*copy_backward�� copy() ��������Ԫ�أ����Ǵ����һ��Ԫ�ؿ�ʼֱ����һ��Ԫ��*/
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	// ����Ԫ��
	element[theIndex] = theElement;
	listSize++;
}
template <class T>
void arrayList<T>::output(std::ostream &out)const { // �����Ա���뵽�����
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T>&x) {
	x.output(out);
	return out;
}
#endif
