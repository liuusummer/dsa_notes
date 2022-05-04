/* 链表二叉树的节点结构 */
/*     
	节点有两个指针域  leftChild rightChild
	一个element域
*/
#ifndef BinaryTreeNode_
#define BinaryTreeNode_
template <class T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T> *leftChild;   // 左子树
	binaryTreeNode<T> *rightChild;  // 右子树
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