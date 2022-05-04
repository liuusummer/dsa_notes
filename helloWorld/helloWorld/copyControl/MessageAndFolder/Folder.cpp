#include "Folder.h"
void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    for (auto &mp : lhs.messages)
        mp->folders.erase(&lhs);
    for (auto &mp : rhs.messages)
        mp->folders.erase(&rhs);
    swap(lhs.messages, rhs.messages);
    for (auto &mp : lhs.messages)
        mp->folders.insert(&lhs);
    for (auto &mp : rhs.messages)
        mp->folders.insert(&rhs);
}
void Folder::addMsg(Message *mp) {
    messages.insert(mp);
}

void Folder::remMsg(Message *mp) {
    messages.erase(mp);
}

void Folder::save(Message &m) {
    messages.insert(&m);
    m.folders.insert(this);
}

void Folder::remove(Message &m) {
    messages.erase(&m);
    m.folders.erase(this);
}

Folder::Folder(const Folder &f) : messages(f.messages) {
    for (auto &mp : messages)
        mp->folders.insert(this);
}

Folder &Folder::operator=(const Folder &rhs) {
    for (auto &mp : messages)
        mp->folders.erase(this);
    messages = rhs.messages;
    for (auto &mp : messages)
        mp->folders.insert(this);
    return *this;
}

Folder::~Folder() {
    for (auto &mp : messages)
        mp->folders.erase(this);
}
