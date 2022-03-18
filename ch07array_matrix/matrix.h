/* ������matrix */
/*
*   ����������Ѿ���ӳ�䵽һ��һά������
*	ӳ�亯��Ϊ��
	map(i,j) = i*���������+j
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
	int theRows;    // ���������
	int theColumns; // ���������
	T *element;   // ����element
};

template <class T>
matrix<T>::matrix(int theRows, int theColumns) {
	// constructor
	// ���캯��������������������������0�ľ���
	// Ҳ����0*0����
	
	// �������������
	if (theRows < 0 || theColumns < 0) {
		throw illegalParameterValue("Rows and columns must be >= 0");
	}
	if ((theRows == 0 || theColumns == 0)
		&& (theRows != 0 || theColumns != 0)) {
		throw illegalParameterValue("Either both or neither rows and columns should be zero");
	}
	// ��������
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows * theColumns];
}
template <class T>
matrix<T>::matrix(const matrix<T> &m) {
	// copy constructor
	// ��������
	this->theRows = m.theRows;
	this->theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	// ����ÿһ��Ԫ��
	copy(m.element,
		m.element + theRows * theColumns,
		element);
}
template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T> &m) {
	// ��ֵ
	if (this != &m) {
		delete []element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		// ����ÿһ��Ԫ��
		std::copy(m.element,
			m.element + theRows * theColumns,
			element);
	}
	return *this;
}
template <class T>
T& matrix<T>::operator()(int i, int j)const {
	// ���ض�Ԫ��element(i,j)������
	if (i<1 || i>theRows
		|| j<1 || j>theColumns) {
		throw matrixIndexOutOfBounds();
	}
	return element[(i - 1) * theColumns + j - 1];
}
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &m)const {
	// ���ؾ���w = (*this) + m
	if (theRows != m.theRows || theColumns != m.theColumns) {
		throw matrixSizeMismatch();
	}
	// ���ɽ������
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = element[i] + m.element[i];
	}
	return w;
}
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &m)const {
	// ���ؾ���w = (*this) - m
	if (theRows != m.theRows || theColumns != m.theColumns) {
		throw matrixSizeMismatch();
	}
	// ���ɽ������
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = element[i] - m.element[i];
	}
	return w;
}
template <class T>
matrix<T> matrix<T>::operator-()const {
	// ���ؾ���w = -(*this)
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++) {
		w.element[i] = -element[i];
	}
	return w;
}
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &m)const {
	// ����˷�  ���ؽ������w = (*this)*m
	if (theColumns != m.theRows) {
		throw matrixSizeMismatch();
	}
	matrix<T> w(theRows, m.theColumns);
	// �������*this,m,w���α��ҳ�ʼ����Ϊ��1��1����λ
	int ct = 0, cm = 0, cw = 0;
	// ������i,j����w(i,j)
	for (int i = 1; i <= theRows; i++) {
		// �������ĵ�i��
		for (int j = 1; j <= m.theColumns; j++) {
			// ����w(i,j)�ĵ�һ��
			T sum = element[ct] * m.element[cm];

			// �ۼ�����������
			for (int k = 2; k <= theColumns; k++) {
				ct++;    // *this�е�i�е���һ��
				cm += m.theColumns; // m�е�j���е���һ��
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // �洢��w(i,j)

			// ���е����͵�һ�����¿�ʼ
			ct -= theColumns - 1;
			cm = j;
		}

		// ����һ�к͵�һ�����¿�ʼ
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
