#ifndef LinkedBinaryTree_h_
#define LinkedBinaryTree_h_

using namespace std;

#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "D:\\dsa_notes\\myExceptions.h"

template <class E>
class linkedBinaryTree :public binaryTree<binaryTreeNode<E>> {
public:
	linkedBinaryTree() { root = nullptr; treeSize = 0; }
	~linkedBinaryTree() { erase(); }
	bool empty()const { return treeSize == 0; }
	int size()const { return treeSize; }
	E *rootElement() const;
	void makeTree(const E &element,
		linkedBinaryTree<E> &, linkedBinaryTree<E> &);
	linkedBinaryTree<E> &removeLeftSubtree();
	linkedBinaryTree<E> &removeRightSubtree();
	void preOrder(void (*theVisit)(binaryTreeNode<E> *)) {
		visit = theVisit;
		preOrder(root);
	}
	void inOrder(void (*theVisit)(binaryTreeNode<E> *)) {
		visit = theVisit;
		inOrder(root);
	}
	void postOrder(void (*theVisit)(binaryTreeNode<E> *)) {
		visit = theVisit;
		postOrder(root);
	}
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	// void levelOrderOutput() { levelOrder(output); cout << endl; }

	void erase() {
		postOrder(dispose);
		root = nullptr;
		treeSize = 0;
	}
	int height() { return height(root); }
protected:
	binaryTreeNode<E> *root;   // 指向根的指针
	int treeSize;    // 数的节点个数
	static void (*visit) (binaryTreeNode<E> *);  // 访问函数
	static int count;    // count nodes
	static void preOrder(binaryTreeNode<E> *t);
	static void inOrder(binaryTreeNode<E> *t);
	static void postOrder(binaryTreeNode<E> *t);
	static void countNodes(binaryTreeNode<E> *t) {
		visit = addToCount;
		count = 0;
		preOrder(t);
	}
	static void dispose(binaryTreeNode<E> *t) { delete t; }
	static void output(binaryTreeNode<E> *t) {
		cout << t->element << ' ';
	}
	static void addToCount(binaryTreeNode<E> *t) {
		count++;
	}
	static int height(binaryTreeNode<E> *t);
};
// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int> *);
// void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster> *);
void (*linkedBinaryTree<pair<int, int> >::visit)(binaryTreeNode<pair<int, int> > *);
void (*linkedBinaryTree<pair<const int, char> >::visit)(binaryTreeNode<pair<const int, char> > *);
void (*linkedBinaryTree<pair<const int, int> >::visit)(binaryTreeNode<pair<const int, int> > *);

template<class E>
E *linkedBinaryTree<E>::rootElement() const {// Return NULL if no root. Otherwise, return pointer to root element.
	if (treeSize == 0)
		return nullptr;  // no root
	else
		return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E &element,
	linkedBinaryTree<E> &left, linkedBinaryTree<E> &right) {
	// Combine left, right, and element to make new tree.
	// left, right, and this must be different trees.
	// create combined tree
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;

	// deny access from trees left and right
	left.root = right.root = nullptr;
	left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeLeftSubtree() {
	// Remove and return the left subtree.
   // check if empty
	if (treeSize == 0)
		throw emptyTree();

	// detach left subtree and save in leftSubtree
	linkedBinaryTree<E> leftSubtree;
	leftSubtree.root = root->leftChild;
	count = 0;
	leftSubtree.treeSize = countNodes(leftSubtree.root);
	root->leftChild = nullptr;
	treeSize -= leftSubtree.treeSize;

	return leftSubTree;
}
template<class E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeRightSubtree() {// Remove and return the right subtree.
   // check if empty
	if (treeSize == 0)
		throw emptyTree();

	// detach right subtree and save in rightSubtree
	linkedBinaryTree<E> rightSubtree;
	rightSubtree.root = root->rightChild;
	count = 0;
	rightSubtree.treeSize = countNodes(rightSubtree.root);
	root->rightChild = nullptr;
	treeSize -= rightSubtree.treeSize;

	return rightSubTree;
}
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t) {// Preorder traversal.
	if (t != nullptr) {
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t) {// Inorder traversal.
	if (t != nullptr) {
		inOrder(t->leftChild);
		linkedBinaryTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t) {// Postorder traversal.
	if (t != nullptr) {
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}
template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) {// Return height of tree rooted at *t.
	if (t == nullptr)
		return 0;                    // empty tree
	int hl = height(t->leftChild);  // height of left
	int hr = height(t->rightChild); // height of right
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
#endif