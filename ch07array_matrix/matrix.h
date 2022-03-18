/* 矩阵类matrix */
/*
*   用行主次序把矩阵映射到一个一维数组中
*	映射函数为：
	map(i,j) = i*矩阵的列数+j
*
*/
#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>
#include <algorithm>
#include "D:\\dsa_notes\\myExceptions.h"

template <class T>
class matrix {
	friend std::ostream &operator<<(std::ostream &,
		const matrix<T> &);
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T> &);
	~matrix() { delete[]element; }
	int rows()const { return theRows; }
	int columns()const { return theColumns; }

	T &operator()(int i, int j)const;

	matrix<T> &operator=(const matrix<T> &);
	// matrix<T> operator+()const;  // unary plus
	matrix<T> operator+(const matrix<T> &)const;
	matrix<T> operator-()const; // unary minus
	matrix<T> operator-(const matrix<T> &)const;
	matrix<T> operator*(const matrix<T> &)const;
	matrix<T> &operator+=(const T &);

private:
	int theRows;    // 矩阵的行数
	int theColumns; // 矩阵的列数
	T *element;   // 数组element
};

template <class T>
matrix<T>::matrix(int theRows, int theColumns) {
	// constructor
	// 构造函数不仅生成行数和列数都大于0的矩阵
	// 也生成0*0矩阵
	
	// 检查行数和列数
	if (theRows < 0 || theColumns < 0) {
		throw illegalParameterValue("Rows and columns must be >= 0");
	}
	if ((theRows == 0 || theColumns == 0)
		&& (theRows != 0 || theColumns != 0)) {
		throw illegalParameterValue("Either both or neither rows and columns should be zero");
	}
	// 创建矩阵
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows * theColumns];
}
template <class T>
matrix<T>::matrix(const matrix<T> &m) {
	// copy constructor
	// 创建矩阵
	this->theRows = m.theRows;
	this->theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	// 复制每一个元素
	copy(m.element,
		m.element + theRows * theColumns,
		element);
}
template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T> &m) {
	// 赋值
	if (this != &m) {
		delete []element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		// 复制每一个元素
		std::copy(m.element,
			m.element + theRows * theColumns,
			element);
	}
	return *this;
}
template <class T>
T& matrix<T>::operator()(int i, int j)const {
	// 返回对元素element(i,j)的引用
	if (i<1 || i>theRows
		|| j<1 || j>theColumns) {
		throw matrixIndexOutOfBounds();
	}
	return element[(i - 1) * theColumns + j - 1];
}
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &m)const {
	// 返回矩阵w = (*this) + m
	if (theRows != m.theRows || theColumns != m.theColumns) {
		throw matrixSizeMismatch();
	}
	// 生成结果矩阵
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = element[i] + m.element[i];
	}
	return w;
}
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &m)const {
	// 返回矩阵w = (*this) - m
	if (theRows != m.theRows || theColumns != m.theColumns) {
		throw matrixSizeMismatch();
	}
	// 生成结果矩阵
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = element[i] - m.element[i];
	}
	return w;
}
template <class T>
matrix<T> matrix<T>::operator-()const {
	// 返回矩阵w = -(*this)
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = -element[i];
	}
	return w;
}
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &m)const {
	// 矩阵乘法  返回结果矩阵w = (*this)*m
	if (theColumns != m.theRows) {
		throw matrixSizeMismatch();
	}
	matrix<T> w(theRows, m.theColumns);
	// 定义矩阵*this,m,w的游标且初始化以为（1，1）定位
	int ct = 0, cm = 0, cw = 0;
	// 对所有i,j计算w(i,j)
	for (int i = 1; i <= theRows; i++) {
		// 计算矩阵的第i行
		for (int j = 1; j <= m.theColumns; j++) {
			// 计算w(i,j)的第一项
			T sum = element[ct] * m.element[cm];

			// 累加其余所有项
			for (int k = 2; k <= theColumns; k++) {
				ct++;    // *this中第i行的下一项
				cm += m.theColumns; // m中第j列中的下一项
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // 存储在w(i,j)

			// 从行的起点和第一列重新开始
			ct -= theColumns - 1;
			cm = j;
		}

		// 从下一行和第一列重新开始
		ct += theColumns;
		cm = 0;
	}
	return w;
}
template <class T>
matrix<T> &matrix<T>::operator+=(const T &x) {
	for (int i = 0; i < theRows * theColumns; i++) {
		element[i] += x;
	}
	return *this;
}
template<class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
	int k = 0;
	for (int i = 0; i < m.theRows; i++) {
		for (int j = 0; j < m.theColumns; j++) {
			out << m.element[k++] << "  ";
		}
		out << std::endl;
	}
	return out;
}
// for some reason compiler can't create this on its own
std::ostream &operator<<(std::ostream &out, const matrix<int> &m) {// Put matrix m into the stream out.
 // One row per line.
	int k = 0;  // index into element array
	for (int i = 0; i < m.theRows; i++) {// do row i
		for (int j = 0; j < m.theColumns; j++)
			out << m.element[k++] << "  ";

		// row i finished
		out << endl;
	}

	return out;
}
#endif
