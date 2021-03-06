#include <iostream>
#include "String.h"

std::allocator<char> String::alloc;

// 接受一个const char*参数的构造函数   (利用push_back)
String::String(const_iterator ci) :String() {
    while (ci && *ci != '\0') {
        push_back(*ci++);
    }
}

// String接受初始值列表的构造函数  (利用push_back)
String::String(std::initializer_list<char> il) :String() {
    for (const auto &c : il) {
        push_back(c);
    }
}

void String::push_back(const_reference c) {
    if (size() == capacity())
        reallocate(empty() ? 1 : 2 * capacity());
    alloc.construct(first_free++, c);
}

void String::pop_back() {
    if (!empty())
        alloc.destroy(--first_free);
}

void String::reserve(size_type n) {
    if (n > capacity()) {
        reallocate(n);
    }
}

void String::resize(size_type n, const_reference c) {
    if (n > size()) {
        for (int i = n - size(); i > 0; --i)
            push_back(c);
    }
    else if (n < size()) {
        for (int i = size() - n; i > 0; --i)
            pop_back();
    }
}

void String::reallocate(size_type n) {
    auto new_first_elem = alloc.allocate(n);
    auto new_first_free = new_first_elem;
    for (auto it = begin(); it != end(); ++it)
        alloc.construct(new_first_free++, std::move(*it));
    // the above three lines of code can be replaced by the following code:
    //auto new_first_free = std::uninitialized_copy(
    //    std::make_move_iterator(begin()),
    //    std::make_move_iterator(end()), new_first_elem);
    free();
    first_elem = new_first_elem;
    first_free = new_first_free;
    cap = first_elem + n;
}

void String::free() {
    while (!empty())
        alloc.destroy(--first_free);
    alloc.deallocate(first_elem, capacity());
    first_elem = first_free = cap = nullptr;
}

String::String(const String &rhs) {
    std::cout << "拷贝构造函数\n";
    first_elem = alloc.allocate(rhs.size());
    first_free = cap = std::uninitialized_copy(rhs.begin(), rhs.end(),
        first_elem);
}

String::~String() {
    free();
}

String &String::operator=(const String &rhs) {
    std::cout << "拷贝赋值运算符\n";
    auto new_first_elem = alloc.allocate(rhs.size());
    auto new_first_free = std::uninitialized_copy(rhs.begin(), rhs.end(),
        new_first_elem);
    free();
    first_elem = new_first_elem;
    first_free = cap = new_first_free;
    return *this;
}

String &String::operator=(const_iterator ci) {
    *this = String(ci);
    return *this;
}

String::String(String &&s)noexcept:first_elem(s.first_elem),
    first_free(s.first_free),cap(s.cap) {
    std::cout << "移动构造函数\n";
    s.first_elem = s.first_free = s.cap = nullptr;
}
String &String::operator=(String &&rhs)noexcept {
    std::cout << "移动赋值运算符\n";
    if (this != &rhs) {
        free();
        first_elem = rhs.first_elem;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.first_elem = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}


std::string String::str() const {
    return std::string(cbegin(), cend());
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.str();
    return os;
}