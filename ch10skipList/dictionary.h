#ifndef Dictionary
#define Dictionary
using namespace std;
template <class K,class E>
class dictionary {
public:
	virtual ~dictionary() {}
	virtual bool empty()const = 0;
					// ����true,���ҽ����ֵ�Ϊ��
	virtual int size()const = 0;
					// �����ֵ������Ե���Ŀ
	virtual pair<const K, E> *find(const K &)const = 0;
					// ����ƥ�����Ե�ָ��
	virtual void erase(const K &) = 0;
					// ɾ��ƥ�������
	virtual void insert(const  pair<const K, E> &) = 0;
					// ���ֵ��в���һ������
};
#endif