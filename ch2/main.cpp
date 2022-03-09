#include <iostream>
#include <exception>

template <class T>
int sequentialSerach(T a[], int n, const T &x) {
	// ������a[0:n-1]��Ѱ��x
	// ����ҵ����ظ�Ԫ��λ�� û���ҵ�����-1
	int i;
	for (i = 0; i < n && a[i] != x; i++);
	if (i == n) return -1;
	else return i;
}

template <class T>
T polyEval(T coeff[], int n, const T &x) {
	// ����n�׶���ʽ�ڵ�x����ֵ��ϵ��Ϊcoeff[0:n]
	T y = 1, value = coeff[0];
	for (int i = 1; i <= n; i++) {
		y *= x;
		value += y * coeff[i];
	}
	return value;
}

template <class T>
T horner(T coeff[], int n, const T &x) {
	// �� horner ���� ����n�׶���ʽ��x����ֵ��ϵ����coeff[0:n]
	T value = coeff[n];
	for (int i = n; i >= 1; i--) {
		value = value * x + coeff[i - 1];
	}
	/*for (int i = 1; i <= n; i++) {
		value = value * x + coeff[n - i];
	}*/
	return value;
}




template<class T>
void rank(T a[], int n, int r[]) {
	// ������a[0:n-1]��n��Ԫ��������  input:4 3 9 3 7   output:2 0 4 1 3
	// �����r[0:n-1]�з���

	for (int i = 0; i < n; i++) {
		r[i] = 0; // ��ʼ��
	}
	// �Ƚ�����Ԫ�ض�

	for (int i = 1; i < n; i++) {   // ������ĵڶ���Ԫ�ؿ�ʼ
		for (int j = 0; j < i; j++) {   // �Ƚ�����ǰ���Ԫ��
			if (a[j] <= a[i]) r[i]++;
			else    // ���ǰ���ֵ<=��  ��������rank
				r[j]++;  // ǰ���ֵ>�� ������ֵ��rank
			// �����������ظ��Ƚ� ֻ�Ƚ���ÿ��Ԫ������ǰ���Ԫ��
		}
	}
}

template <class T>
void rearrange(T a[], int n, T r[]) {
	// ���ø�������u[] ����rank�ļ������� r[]��a[]��ranking
	T *u = new T[n];
	// ��a��Ԫ�ظ���u  ����rank��Ӧ�����Ե�λ����
	for (int i = 0; i < n; i++) {
		u[r[i]] = a[i];
	}
	for (int i = 0; i < n; i++) {
		a[i] = u[i];
	}
	delete[]u;


}

template<class T>
int indexOfMax(T a[], int n) {
	// ��������a[0:n-1]�����Ԫ��   ��������
	/*if (n <= 0) {
	* // �쳣����
		throw(std::out_of_range);
	}*/
	int index = 0;
	for (int i = 1; i < n; i++) {
		if (a[index] < a[i]) {
			index = i;
		}
	}
	return index;
}
template<class T>
void selectionSort(T a[], int n) {
	// ѡ�����������ҵ�����Ԫ�ؽ����ƶ���a[n-1]����ʣ�µ�n-1��Ԫ�����ҳ�����Ԫ��
	// �����ƶ���a[n-2]
	for (int i = n; i > 1; i--) {
		int index = indexOfMax(a, i);
		std::swap(a[index], a[i - 1]);
	}
}

template<class T>
void bubble(T a[], int n) {
	// һ��ð�ݹ��̣�����Ԫ�رȽϣ������ߵĴ����ұߣ��򽻻�
	// һ��ð�ݽ���������Ԫ�ؿ϶������Ҷ�
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			std::swap(a[i], a[i + 1]);
		}
	}
}
template <class T>
void bubbleSort_(T a[], int n) {
	// ��a[0:n-1]ð������
	for (int i = n; i > 1; i--) {
		bubble(a, i);
	}
}

template <class T>
void insert(T a[], int &n, const T &x) {
	// ��x���뵽��������a[0:n-1]
	// ����a����������n
	int i;
	for (int i = n - 1; i >= 0 && x < a[i]; i--) {
		a[i + 1] = a[i];
	}
	a[i + 1] = x;   // ѭ������ʱ����λ��
	n++; // array ����һ��Ԫ��
}

template<class T>
void rearrange(T a[], int n, int r[]) {
	// ԭ������   r[]�������a[]��rank
	for (int i = 0; i < n; i++) {
		while (r[i] != i) {   // ��ÿ��Ԫ�أ��ҵ�rank[i]=i��Ԫ�أ�
								// ������ǣ��ͽ�������ֵ��rankֵ
			int temp = r[i];    
			std::swap(a[i], a[temp]);
			std::swap(r[i], r[temp]);
		}
	}
}

template<class T>
void selectionSort_(T a[], int n) {
	// ��ʱ��ֹ��ѡ������
	bool sorted = false;
	for (int size = n; (!sorted) && (size > 1); size--) {   // ֻ����������½��в���
		int indexOfMax = 0;
		sorted = true;
		for (int j = 1; j < size; j++) {
			if (a[indexOfMax] <= a[j]) {
				indexOfMax = j;    // ˵��������ģ���С����  sorted���ø���  ����Ϊtrue
									// ���ֽ�����whileֱ�ӽ���
			}
			else {
				sorted = false;   // �������� sorted��Ϊfalse
			}
		}
		std::swap(a[indexOfMax], a[size - 1]);  // �������ĺ����һ��Ԫ��

	}
}

template <class T>
bool bubble(T a[], int n) {
	// ������a[0:n-1]������Ԫ��������
	bool swapped = false;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			std::swap(a[i], a[i + 1]);
			swapped = true;    // ��������˽���  swapped��Ϊtrue
		}
	}
	return swapped; // û�з������� 
}

template<class T>
void bubbleSort(T a[], int n) {
	for (int size = n; (size > 1) && bubble(a, size); size--) {
		; // ����� 
	}
}

template<class T>
void insertSort(T a[], int n) {
	// ��a[0:n-1]��������  
	for (int i = 1; i < n; i++) {
		T temp = a[i];  // ��a[1]��ʼ  ������ǰ���Ԫ�رȽ�  ���뵽���ʵ�λ��
		int j;
		for (j = i - 1; j >= 0 && (a[j] > temp); j--) {    // �ҵ�ǰ���һ����temp���Ԫ��
			a[j + 1] = a[j];   // ���κ����ڳ�λ��
		}
		a[j + 1] = temp;  // �����ֵ

	}
}

template<class T>
void transpose(T **a, int rows) {
	// ԭ����ɾ���a[0:rows-1][0:rows-1]��ת��
	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; i++) {
			// ���ڵ�i��  ֻҪ���ǵ�i��֮�����
			std::swap(a[i][j], a[j][i]);
		}
	}
}
int main() {

	//int test[] = { 6,5,8,4,3,1 };
	//const int num = sizeof(test) / sizeof(test[0]);
	////selectionSort(test, sizeof(test) / sizeof(test[0]));
	//bubbleSort(test, num);
	//for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
	//	std::cout << test[i] << " ";
	//}
	/*int a[4] = { 1,2,3,4 };
	int x = 7;
	std::cout << horner(a, 3, x);*/

	return 0;
}
