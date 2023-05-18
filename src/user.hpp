#ifndef __USER_HPP__
#define __USER_HPP__
#include "base.hpp"
#include <iostream>
#include <string>

using namespace std;

class User : public Base {
public:
    User(ull num, ull value, const string& s)
        : Base(num, value, s) {};
    User(const User& user)
        : Base(user) {};
    User(User&& user)
        : Base(user) {};
    ostream& println(ostream& out = cout, char end ='\n', char separator = '\t') const;
    bool operator==(const User&);
    User& operator=(const User& b);
    User& operator-=(ull t);
    friend ostream& operator<<(ostream&, const User&);
};
#endif //__USER_HPP__