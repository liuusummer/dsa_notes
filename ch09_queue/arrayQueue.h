/* 用环形数组来表示队列 */
/* derived from class queue("queue.h")*/
/* location(i) = (location(队列首元素)+i) % arrayLength */
#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

#include "queue.h"
#include "D:\\dsa_notes\\myExceptions.h"
#include <sstream>

template <class T>
class arrayQueue :public queue<T>{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[]queue; };
	bool empty()const { return theFront == theBack; }
	int size()const {
		return (theBack - theFront + arrayLength) % arrayLength;
	}
	T &front() {
		// 返回首元素
		if (theFront == theBack) {
			throw queueEmpty();
		}
		return queue[(theFront + 1) % arrayLength];
	}
	T &back() {
		// 返回尾元素
		if (theFront == theBack) {
			throw queueEmpty();
		}
		return queue[theBack];
	}
	void pop();
	void push(const T &theElement);
private:
	int theFront; // 1 counterclockwise from theFront element
					// 沿逆时针，指向队列首元素的下一个位置
	int theBack;   // 尾元素的位置
	int arrayLength;  // queue capacity
	T *queue;      // 元素数组
};
template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initialcapacity = " << initialCapacity << " Must be >= 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = theBack = 0;
}
template <class T>
void arrayQueue<T>::pop() {
	// 删除首元素
	if (theFront == theBack) {
		throw queueEmpty();
	}
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();  // destructor
}
template <class T>
void arrayQueue<T>::push(const T &theElement) {
	// 把元素theElement加入到队列种

	// 如果有需要增加数组长度
	if ((theBack + 1) % arrayLength == theFront) {
		// 加倍数组长度
		// 分配新的数组空间
		T *newQueue = new T[2 * arrayLength];
		// 把原数组元素拷贝到新数组
		int start = (theFront + 1) % arrayLength;
		// ???
		if (start < 2)
			// no wrap around
			copy(queue + start, queue + start + arrayLength - 1, newQueue);
		else {  // queue wraps around
			copy(queue + start, queue + arrayLength, newQueue);
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}

		// switch to newQueue and set theFront and theBack
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;   // queue size arrayLength - 1
		arrayLength *= 2;
		queue = newQueue;
	}
	// put theElement at the theBack of the queue
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}

#endif