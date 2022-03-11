#ifndef CHANGELENGTH1D_H_
#define CHANGELENGTH1D_H_
#include "myExceptions.h"

using namespace std;

/*改变一个一维数组长度*/
template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T *temp = new T[newLength];              // new array
    int number = min(oldLength, newLength);  // number to copy
    copy(a, a + number, temp);
    delete[] a;                             // deallocate old memory
    a = temp;
}

#endif

