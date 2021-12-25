#include <iostream>

#include <algorithm>
template<class T>
T binarySearch(T a[], int n, const T &x) {
	// 在有序数组中寻找元素x
	// 如果存在，就返回元素x的位置  否则返回-1

	unsigned int left = 0;       // 数据段的左端
	unsigned int right = n - 1;  // 数据段的右端
	while (left != right) {
		int middle = (left + right) / 2;   // 数据段的中间
		if (x == a[middle]) {      // 如果中间刚好是要找的x  返回
			return middle;
		}
		if (x > a[middle]) {    // x比中间的大 说明要在后半段找
									// 更新左端
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}
	return -1;   // while结束了 还没有return 没有找到 return-1
}
int main() {




	return 0;
}