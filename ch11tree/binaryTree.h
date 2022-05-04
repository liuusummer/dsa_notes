#ifndef BinaryTree_
#define BinaryTree_
/*  二叉树抽象类 binaryTree */
template <class T>
class binaryTree {
public:
	virtual ~binaryTree() {}
	virtual bool empty()const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void (*)(T *)) = 0;
			// 参数void (*)(T*) 函数类型
	virtual void inOrder(void (*)(T *)) = 0;
	virtual void postOrder(void (*) (T *)) = 0;
	// virtual void levelOrder(void (*) (T *)) = 0;
};




#endif