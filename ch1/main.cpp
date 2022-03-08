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
	x = new T * [numberOfRows];  // ����numbersOfRows��T*�Ϳռ� �����洢��ָ��
	for (int i = 0; i < numberOfRows; i++) {
		x[i] = new T[rowSize[i]];
	}
}

template<class T>
void permutations(T list[], int k, int m) {
	// �������list[k:m-1]��ȫ����
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

//ʹ��STL�㷨next_permutation������
// next_permutation(start,end,compare) �Է�Χ[start,end)�ڵ�Ԫ�أ����ֵ�˳��
// ������һ����������С����ҽ���������д���ʱ����ֵΪtrue
template<class T>
void permutationsVersion2(T list[], int m) {
	// ��list[0:m-1]ȫ����
	std::sort(list, list + m); // ����
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


