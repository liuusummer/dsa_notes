#include <iostream>

#include <algorithm>
template<class T>
T binarySearch(T a[], int n, const T &x) {
	// ������������Ѱ��Ԫ��x
	// ������ڣ��ͷ���Ԫ��x��λ��  ���򷵻�-1

	unsigned int left = 0;       // ���ݶε����
	unsigned int right = n - 1;  // ���ݶε��Ҷ�
	while (left != right) {
		int middle = (left + right) / 2;   // ���ݶε��м�
		if (x == a[middle]) {      // ����м�պ���Ҫ�ҵ�x  ����
			return middle;
		}
		if (x > a[middle]) {    // x���м�Ĵ� ˵��Ҫ�ں�����
									// �������
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}
	return -1;   // while������ ��û��return û���ҵ� return-1
}
int main() {




	return 0;
}