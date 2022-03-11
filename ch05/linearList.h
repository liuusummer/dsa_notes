#ifndef LINEARLIST_H_
#define LINEARLIST_H_
#include <iostream>
// һ�����Ա�ĳ�������
template <class T>
class linearList {
public:
	virtual ~linearList() {};
	//���ҽ������Ա�Ϊ�շ���true
	virtual bool empty()const = 0;
	// �������Ա�Ԫ�صĸ���
	virtual int size()const = 0;
	// ��������ΪtheIndex��Ԫ��
	virtual T &get(int theIndex)const = 0;
	// ����Ԫ��theElement��һ�γ���ʱ������
	virtual int indexOf(const T &theElement)const = 0;
	// ɾ������ΪtheIndex��Ԫ��
	virtual void erase(int theIndex) = 0;
	// ��theElement�������Ա�������ΪtheIndex��λ����
	virtual void insert(int theIndex, const T &theElement) = 0;
	// �����Ա���������out
	virtual void output(std::ostream &out)const = 0;
};

#endif

