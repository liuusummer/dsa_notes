#include <iostream>
#include <sstream>
#include <algorithm>
/* �����Լ����쳣��*/
class illegalParameterValue {
public:
	illegalParameterValue() :
		message("Illegal parameter value") {
	}
	illegalParameterValue(std::string theMessage){
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};


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

//�ı�һ��һά���鳤��
template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
	if (newLength < 0) {
		throw illegalParameterValue("new length must be >= 0");
	}
	T *temp = new T(newLength);   // ������
	int number = std::min(oldLength, newLength);  // ��Ҫ���Ƶ�Ԫ�ظ���
	std::copy(a, a + number, temp);
	delete[]a;    // �ͷ���������ڴ�ռ�
	a = temp;
}

/*   
* ���������linearList��������arrayList
* arrayList��һ�������࣬����ʵ�ֳ�����linearList�����з�����������linearListû�������ķ���
* ����capacity������������element��ǰ�ĳ���
* ����checkIndexҪȷ��һ��Ԫ���ڷ�Χ0��listSize-1�ڵ�����
*/
template<class T>
class arrayList :public linearList<T>{
public:
	// ���캯�����������캯������������
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT����
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

	// ��������
	int capacity()const { return arrayLength; }
protected:
	void checkIndex(int theIndex)const;
				// ������theIndex��Ч�����׳��쳣
	T *element;    // �洢���Ա�Ԫ�ص�һά����
	int arrayLength;  // һά���������
	int listSize;     // ���Ա��Ԫ�ظ���
};

// ���캯���Ϳ������캯��
template <class T>
arrayList<T>::arrayList(int initialCapacity) { // ���캯��
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial Capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {   // �������캯��
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}


int main() {
	/*arrayListʵ����*/
	// ������������Ϊ100�����Ա�
	// linearList<int> *x = new arrayList<int>(100);
	arrayList<double> y(100);

	std::cout << y.size();
}