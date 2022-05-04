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
	// folders被隐式初始化为空集合
	explicit Message(const std::string &str = "") :
		contents(str) {
	}

	// 拷贝控制成员，用来管理指向本Message的指针
	Message(const Message &); // copy constructor
	Message &operator=(const Message &); // copy assignment operator
	~Message();  // destructor

	// 从给定Folder集合中添加/删除本Message
	void save(Folder &);
	void remove(Folder &);
private:
	std::string contents;  // 实际消息文本
	std::set<Folder *> folders;   // 包含本message的Folder

	// 拷贝构造函数  拷贝赋值运算符和析构函数所使用的工具函数

	// 将本Message添加到指定参数的Folder中
	void add_to_Folders(const Message &);
	// 从folders中的每个Folder中删除本Message
	void remove_from_Folders();
};

void swap(Message &, Message &);








#endif