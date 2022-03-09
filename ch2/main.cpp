#include <iostream>
#include <exception>

template <class T>
int sequentialSerach(T a[], int n, const T &x) {
	// 在数组a[0:n-1]中寻找x
	// 如果找到返回该元素位置 没有找到返回-1
	int i;
	for (i = 0; i < n && a[i] != x; i++);
	if (i == n) return -1;
	else return i;
}

template <class T>
T polyEval(T coeff[], int n, const T &x) {
	// 计算n阶多项式在点x处的值，系数为coeff[0:n]
	T y = 1, value = coeff[0];
	for (int i = 1; i <= n; i++) {
		y *= x;
		value += y * coeff[i];
	}
	return value;
}

template <class T>
T horner(T coeff[], int n, const T &x) {
	// 用 horner 法则 计算n阶多项式在x处的值，系数是coeff[0:n]
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
	// 给数组a[0:n-1]的n个元素排名次  input:4 3 9 3 7   output:2 0 4 1 3
	// 结果在r[0:n-1]中返回

	for (int i = 0; i < n; i++) {
		r[i] = 0; // 初始化
	}
	// 比较所有元素对

	for (int i = 1; i < n; i++) {   // 从数组的第二个元素开始
		for (int j = 0; j < i; j++) {   // 比较它与前面的元素
			if (a[j] <= a[i]) r[i]++;
			else    // 如果前面的值<=它  递增它的rank
				r[j]++;  // 前面的值>它 递增该值的rank
			// 这样做不会重复比较 只比较了每个元素与它前面的元素
		}
	}
}

template <class T>
void rearrange(T a[], int n, T r[]) {
	// 利用附加数组u[] 根据rank的计数排序 r[]是a[]的ranking
	T *u = new T[n];
	// 将a中元素赋给u  根据rank对应到各自的位置上
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
	// 查找数组a[0:n-1]的最大元素   返回索引
	/*if (n <= 0) {
	* // 异常处理
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
	// 选择排序：首先找到最大的元素将其移动到a[n-1]，在剩下的n-1个元素中找出最大的元素
	// 将它移动到a[n-2]
	for (int i = n; i > 1; i--) {
		int index = indexOfMax(a, i);
		std::swap(a[index], a[i - 1]);
	}
}

template<class T>
void bubble(T a[], int n) {
	// 一次冒泡过程：相邻元素比较，如果左边的大于右边，则交换
	// 一次冒泡结束后，最大的元素肯定在最右端
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			std::swap(a[i], a[i + 1]);
		}
	}
}
template <class T>
void bubbleSort_(T a[], int n) {
	// 对a[0:n-1]冒泡排序
	for (int i = n; i > 1; i--) {
		bubble(a, i);
	}
}

template <class T>
void insert(T a[], int &n, const T &x) {
	// 把x插入到有序数组a[0:n-1]
	// 假设a的容量大于n
	int i;
	for (int i = n - 1; i >= 0 && x < a[i]; i--) {
		a[i + 1] = a[i];
	}
	a[i + 1] = x;   // 循环结束时插入位置
	n++; // array 多了一个元素
}

template<class T>
void rearrange(T a[], int n, int r[]) {
	// 原地重排   r[]保存的是a[]的rank
	for (int i = 0; i < n; i++) {
		while (r[i] != i) {   // 对每个元素，找到rank[i]=i的元素，
								// 如果不是，就交换数组值和rank值
			int temp = r[i];    
			std::swap(a[i], a[temp]);
			std::swap(r[i], r[temp]);
		}
	}
}

template<class T>
void selectionSort_(T a[], int n) {
	// 及时终止的选择排序
	bool sorted = false;
	for (int size = n; (!sorted) && (size > 1); size--) {   // 只在无序情况下进行操作
		int indexOfMax = 0;
		sorted = true;
		for (int j = 1; j < size; j++) {
			if (a[indexOfMax] <= a[j]) {
				indexOfMax = j;    // 说明是有序的：从小到大  sorted不用更改  继续为true
									// 此轮结束后while直接结束
			}
			else {
				sorted = false;   // 并不有序 sorted改为false
			}
		}
		std::swap(a[indexOfMax], a[size - 1]);  // 交换最大的和最后一个元素

	}
}

template <class T>
bool bubble(T a[], int n) {
	// 把数组a[0:n-1]中最大的元素往后移
	bool swapped = false;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			std::swap(a[i], a[i + 1]);
			swapped = true;    // 如果发生了交换  swapped置为true
		}
	}
	return swapped; // 没有发生交换 
}

template<class T>
void bubbleSort(T a[], int n) {
	for (int size = n; (size > 1) && bubble(a, size); size--) {
		; // 空语句 
	}
}

template<class T>
void insertSort(T a[], int n) {
	// 对a[0:n-1]插入排序  
	for (int i = 1; i < n; i++) {
		T temp = a[i];  // 从a[1]开始  依次与前面的元素比较  插入到合适的位置
		int j;
		for (j = i - 1; j >= 0 && (a[j] > temp); j--) {    // 找到前面第一个比temp大的元素
			a[j + 1] = a[j];   // 依次后移腾出位置
		}
		a[j + 1] = temp;  // 插入此值

	}
}

template<class T>
void transpose(T **a, int rows) {
	// 原地完成矩阵a[0:rows-1][0:rows-1]的转置
	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; i++) {
			// 对于第i行  只要考虑第i列之后的列
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
