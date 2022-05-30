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
	// 逐元素copy
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
	// 返回元素theElement第一次出现时的索引
	// 若该元素不存在，则返回-1
	// 查找元素theElement
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	// 确定元素是否找到
	if (theIndex == listSize) {  // 没找到
		return -1;
	}
	else {
		return theIndex;
	}
}

// erase
template <class T>
void arrayList<T>::erase(int theIndex) {  // 删除索引为theIndex的元素
	// 如果元素不存在，则抛出异常
	checkIndex(theIndex);
	// 确定是有效索引后，移动其索引大于theIndex的元素
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	// listSize的值-1
	element[--listSize].~T();   // 析构原来的最后一个元素
}

// insert
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) { // 在theIndex位置插入值theElement
	if (theIndex<0 || theIndex>listSize) {
		// 无效索引
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
	// 有效索引，确定数组是否已满
	if (listSize == arrayLength) {  // 已满  用changeLength1D加倍数组长度
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// 把元素向右移动一个位置
	/*copy_backward像 copy() 那样复制元素，但是从最后一个元素开始直到第一个元素*/ 
	// 改
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	// 插入元素
	element[theIndex] = theElement;
	listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream &out)const { // 把线性表插入到输出流
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}
// operator << 
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x) {
	x.output(out);
	return out;
}
