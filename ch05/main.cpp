#include <iostream>
#include <sstream>
#include <algorithm>
/* 定义自己的异常类*/
class illegalParameterValue {
public:
	illegalParameterValue() :
		message("Illegal parameter value") {
	}
	illegalParameterValue(std::string theMessage){
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};


// 一个线性表的抽象描述
template <class T>
class linearList {
public:
	virtual ~linearList() {};
	//当且仅当线性表为空返回true
	virtual bool empty()const = 0;
	// 返回线性表元素的个数
	virtual int size()const = 0;
	// 返回索引为theIndex的元素
	virtual T &get(int theIndex)const = 0;
	// 返回元素theElement第一次出现时的索引
	virtual int indexOf(const T &theElement)const = 0;
	// 删除索引为theIndex的元素
	virtual void erase(int theIndex) = 0;
	// 把theElement插入线性表中索引为theIndex的位置上
	virtual void insert(int theIndex, const T &theElement) = 0;
	// 把线性表插入输出流out
	virtual void output(std::ostream &out)const = 0;
};

//改变一个一维数组长度
template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
	if (newLength < 0) {
		throw illegalParameterValue("new length must be >= 0");
	}
	T *temp = new T(newLength);   // 新数组
	int number = std::min(oldLength, newLength);  // 需要复制的元素个数
	std::copy(a, a + number, temp);
	delete[]a;    // 释放老数组的内存空间
	a = temp;
}

/*   
* 定义抽象类linearList的派生类arrayList
* arrayList是一个具体类，必须实现抽象类linearList的所有方法。还包括linearList没有声明的方法
* 方法capacity给出的是数组element当前的长度
* 方法checkIndex要确定一个元素在范围0到listSize-1内的索引
*/
template<class T>
class arrayList :public linearList<T>{
public:
	// 构造函数、拷贝构造函数、析构函数
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT方法
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

	// 其他方法
	int capacity()const { return arrayLength; }
protected:
	void checkIndex(int theIndex)const;
				// 若索引theIndex无效，则抛出异常
	T *element;    // 存储线性表元素的一维数组
	int arrayLength;  // 一维数组的容量
	int listSize;     // 线性表的元素个数
};

// 构造函数和拷贝构造函数
template <class T>
arrayList<T>::arrayList(int initialCapacity) { // 构造函数
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
arrayList<T>::arrayList(const arrayList<T> &theList) {   // 拷贝构造函数
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}


int main() {
	/*arrayList实例化*/
	// 创建两个容量为100的线性表
	// linearList<int> *x = new arrayList<int>(100);
	arrayList<double> y(100);

	std::cout << y.size();
}