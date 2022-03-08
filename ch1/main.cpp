#include <iostream>
#include <cstdlib>
#include <exception>
#include <functional>
#include <numeric>
#include <algorithm>
#include <string>
template <class T>
void delete2dArray(T **&x, int numberOfRows) {
	for (int i = 0; i < numberOfRows; i++) {
		delete[]x[i];
	}
	delete[]x;
	x = nullptr;
}

template<class T>
void make2dArray(T **&x, int numberOfRows, int *rowSize) {
	x = new T * [numberOfRows];  // 创建numbersOfRows个T*型空间 用来存储行指针
	for (int i = 0; i < numberOfRows; i++) {
		x[i] = new T[rowSize[i]];
	}
}

template<class T>
void permutations(T list[], int k, int m) {
	// 输出数组list[k:m-1]的全排列
	if (k == m - 1) {
		for (int i = 0; i < m; i++) {
			std::cout << list[i] << " ";
			//std::cout << "    ***k = " << k << " ****  ";
		}
		std::cout << std::endl;
	}
	else {
		for (int i = k; i < m; i++) {
			std::swap(list[k], list[i]);
			permutations(list, k + 1, m);
			std::swap(list[k], list[i]);
		}
	}
}

//使用STL算法next_permutation求排列
// next_permutation(start,end,compare) 对范围[start,end)内的元素，按字典顺序
// 产生下一个更大的排列。当且仅当这个排列存在时返回值为true
template<class T>
void permutationsVersion2(T list[], int m) {
	// 对list[0:m-1]全排列
	std::sort(list, list + m); // 排序
	do {
		copy(list, list + m,
			std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	} while (std::next_permutation(list, list + m));
}

int main() {

	int n;
	int a[20];
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	permutations(a, 2, n);

	int b[3] = { 3,2,4 };
	permutationsVersion2(b, 3);

	return 0;

}


