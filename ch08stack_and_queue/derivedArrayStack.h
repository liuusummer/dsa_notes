#ifndef DERIVEDARRAYSTACK_H_
#define DERIVEDARRAYSTACK_H_
#include "D:\\dsa_notes\\ch05\\arrayList.h"
#include "stack.h"
#include "D:\\dsa_notes\\myExceptions.h"

template <class T>
class derivedArrayStack :private arrayList<T>,
	public stack<T> {
public:
	derivedArrayStack(int initialCapacity = 10)
		:arrayList<T>(initialCapacity){}
	bool empty()const {
		return arrayList<T>::empty();
	}
	int size()const {
		return arrayList<T>::size();
	}
	T &top() {
		if (arrayList<T>::empty()) {
			throw stackEmpty();
		}
		return get(arrayList<T>::size() - 1);
	}
	void pop() {
		if (arrayList<T>::empty()) {
			throw stackEmpty();
		}
		erase(arrayList<T>::size() - 1);
	}
	void push(const T &theElment) {
		// insert(arrayList<T>::size(), theElement);
	}
};

#endif
