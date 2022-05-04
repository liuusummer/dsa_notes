#ifndef message_h_
#define message_h_
#include <string>
#include <set>

class Folder;
class Message {
	friend class Folder;
	friend void swap(Message &, Message &);
	friend void swap(Folder &, Folder &);
public:
	// folders����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const std::string &str = "") :
		contents(str) {
	}

	// �������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message &); // copy constructor
	Message &operator=(const Message &); // copy assignment operator
	~Message();  // destructor

	// �Ӹ���Folder���������/ɾ����Message
	void save(Folder &);
	void remove(Folder &);
private:
	std::string contents;  // ʵ����Ϣ�ı�
	std::set<Folder *> folders;   // ������message��Folder

	// �������캯��  ������ֵ�����������������ʹ�õĹ��ߺ���

	// ����Message��ӵ�ָ��������Folder��
	void add_to_Folders(const Message &);
	// ��folders�е�ÿ��Folder��ɾ����Message
	void remove_from_Folders();
};

void swap(Message &, Message &);








#endif