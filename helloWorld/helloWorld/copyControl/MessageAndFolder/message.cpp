#include "message.h"
void Message::save(Folder &f) {
	folders.insert(&f);   // ������Folder��ӵ����ǵ�Folder�б���
	f.addMsg(this);   // ����Message��ӵ�f��Message������
}
void Message::remove(Folder &f) {
	folders.erase(&f);   // ������Folder�����ǵ�Folder�б����Ƴ�
	f.remMsg(this);    // ����Message��f��Message������ɾ��
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
	remove_from_Folders();   // ��������folder
	contents = rhs.contents;  // ��rhs������Ϣ����
	folders = rhs.folders;	// ��rhs����Folderָ��
	add_to_Folders(rhs);    // ����Message��ӵ���ЩFolder��
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
	// ����contents��Folders�е�ָ��set
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);
	for (auto f : lhs.folders) {

	}
}