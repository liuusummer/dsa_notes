#ifndef HasPtr_h_
#define HasPtr_h_
#include <string>
#include <iostream>

class HasPtr {
    friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {
    }
    HasPtr(const char *cs) :ps(new std::string(cs)), i(0) {}
    HasPtr(const HasPtr &ori)
        : ps(new std::string(*ori.ps)), i(ori.i) {
    }
    ~HasPtr();

    HasPtr &operator=(const HasPtr &rhs);

    // <操作 在一个vector中调用sort 测试输出
    bool operator<(const HasPtr &)const;


    const std::string &get() const { return *ps; }
    void set(const std::string &s) { *ps = s; }

private:
    std::string *ps;
    int i;
};

HasPtr::~HasPtr() {
    delete ps;
}

HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    // This copy-assignment operator is wrong, see ex13.23 for correct version.
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

inline void swap(HasPtr &, HasPtr &);
void swap(HasPtr &lhs, HasPtr &rhs) {
    std::cout << "Swap between <" << *lhs.ps << "> and <"
        << *rhs.ps << ">" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

bool HasPtr::operator<(const HasPtr &rhs)const {
    return *ps < *rhs.ps;
}
#endif