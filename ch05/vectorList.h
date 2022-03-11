/*
	vectorʵ�ֵĻ�����������Ա�
 */

#ifndef VECTORlIST_H_
#define VECTORLIST_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "linearList.h"
#include "D:\\dsa_notes\\myExceptions.h"

using std::vector;
template <class T>
class vectorList :public linearList<T>{
public:
	// constructor,copy constructor,destructor
	vectorList(int capacity = 10);
	vectorList(const vectorList<T> &);
	~vectorList() { delete element; }

	// ADT ����
	bool empty()const { return element->empty(); }
	int size()const { return(int)element->size(); }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &output)const;

	// ���ӵķ���
	int capacity()const { return (int)element->capacity(); }

	// ���Ա���ʼλ�úͽ���λ�õĵ�����
	typedef typename std::vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }

protected:
	void checkIndex(int theIndex)const;
	std::vector<T> *element;
};

template<class T>
vectorList<T>::vectorList(int initialCapacity) {
	// constructor
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	element = new vector<T>; // ��������Ϊ0�Ŀ�����
	element->reserve(initialCapacity);  // vector������0���ӵ�initialCapacity
}
template <class T>
vectorList<T>::vectorList(const vectorList<T> &theList) {
	// copy constructor
	element = new vector<T>(*theList.element);
}

template <class T>
void vectorList<T>::checkIndex(int theIndex)const {
	if (theIndex < 0 || theIndex >= size()) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	} 
}
template <class T>
T &vectorList<T>::get(int theIndex)const {
	checkIndex(theIndex);
	return (*element)[theIndex];
}
template <class T>
int vectorList<T>::indexOf(const T &theElement)const {
	int theIndex = (int)(find(element->begin(), element->end(), 
		theElement) - element->begin());
	if (theIndex == size()) {
		// not found
		return -1;
	}
	else {
		return theIndex;
	}
}

// erase
template <class T>
void vectorList<T>::erase(int theIndex) {
	// ɾ������ΪtheIndex��Ԫ��
	// ���û�����Ԫ�أ����׳��쳣
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}
// insert
template<class T>
void vectorList<T>::insert(int theIndex, const T &theElement) {
	// ������ΪtheIndex������Ԫ��theElement
	if (theIndex <0 || theIndex>size()) {
		// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}
template<class T>
void vectorList<T>::output(std::ostream &out) const {// Put the list into the stream out.
	copy(element->begin(), element->end(), std::ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
std::ostream &operator<<(std::ostream &out, const vectorList<T> &x) {
	x.output(out); return out;
}


#endif
