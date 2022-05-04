/* ����������Ľڵ�ṹ */
/*     
	�ڵ�������ָ����  leftChild rightChild
	һ��element��
*/
#ifndef BinaryTreeNode_
#define BinaryTreeNode_
template <class T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T> *leftChild;   // ������
	binaryTreeNode<T> *rightChild;  // ������
	// constructor
	binaryTreeNode() {
		leftChild = rightChild = nullptr;
	}
	// 
	binaryTreeNode(const T &theElement) {
		element = theElement;
		leftChild = rightChild = nullptr;
	}
	binaryTreeNode(const T &theElement,
		binaryTreeNode *theLeftChild,
		binaryTreeNode *theRightChild) {
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};



#endif