#include "arrayList.h"

// constructor
template <typename T>
arrayList<T>::arrayList(int initialCapacity) {
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	listSize = 0;
	element = new T[arrayLength];
}

// copy constructor
template <typename T>
arrayList<T>::arrayList(const arratList<T> &theList) {
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	// ��Ԫ��copy
	std::copy(theList.element, theList.element + listSize, element);
}

// checkIndex
template <typename T>
void arrayList<T>::checkIndex(int theIndex)const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

// get
template <typename T>
T &arrayList<T>::get(int theIndex)const {
	checkIndex(theIndex);
	return element[theIndex];
}

// indexOf
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

// erase
template <class T>
void arrayList<T>::erase(int theIndex) {  // ɾ������ΪtheIndex��Ԫ��
	// ���Ԫ�ز����ڣ����׳��쳣
	checkIndex(theIndex);
	// ȷ������Ч�������ƶ�����������theIndex��Ԫ��
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	// listSize��ֵ-1
	element[--listSize].~T();   // ����ԭ�������һ��Ԫ��
}

// insert
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) { // ��theIndexλ�ò���ֵtheElement
	if (theIndex<0 || theIndex>listSize) {
		// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
	// ��Ч������ȷ�������Ƿ�����
	if (listSize == arrayLength) {  // ����  ��changeLength1D�ӱ����鳤��
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// ��Ԫ�������ƶ�һ��λ��
	/*copy_backward�� copy() ��������Ԫ�أ����Ǵ����һ��Ԫ�ؿ�ʼֱ����һ��Ԫ��*/ 
	// ��
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	// ����Ԫ��
	element[theIndex] = theElement;
	listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream &out)const { // �����Ա���뵽�����
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}
// operator << 
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x) {
	x.output(out);
	return out;
}
