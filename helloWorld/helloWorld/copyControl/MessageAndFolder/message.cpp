#include "message.h"
void Message::save(Folder &f) {
	folders.insert(&f);   // 将给定Folder添加到我们的Folder列表中
	f.addMsg(this);   // 将本Message添加到f的Message集合中
}
void Message::remove(Folder &f) {
	folders.erase(&f);   // 将给定Folder从我们的Folder列表中移除
	f.remMsg(this);    // 将本Message从f的Message集合中删除
}
void Message::add_to_Folders(const Message &m) {
	for (auto f : m.folders) {
		f->addMsg(this);
	}
}
Message::Message(const Message &m) :
	contents(m.contents), folders(m.folders) {
	add_to_folders(m);
}
void Message::remove_from_Folders() {
	for (auto f : folders) {
		f->remMsg(this);
	}
}
Message &Message::operator=(const Message &rhs) {
	remove_from_Folders();   // 更新已有folder
	contents = rhs.contents;  // 从rhs拷贝消息内容
	folders = rhs.folders;	// 从rhs拷贝Folder指针
	add_to_Folders(rhs);    // 将本Message添加到那些Folder中
	return *this;
}
Message::~Message() {
	remove_from_Folders();
}
void swap(Message &lhs, Message &rhs) {
	using std::swap;
	for (auto f : lhs.folders) {
		f->remMsg(&lhs);
	}
	for (auto f : rhs.folders) {
		f->remMsg(&rhs);
	}
	// 交换contents和Folders中的指针set
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);
	for (auto f : lhs.folders) {

	}
}