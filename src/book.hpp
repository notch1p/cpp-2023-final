#ifndef __BOOK_HPP__
#define __BOOK_HPP__
#include "base.hpp"
#include <bitset>
#include <iostream>
using namespace std;

class Book : public Base {
private:
    bitset<1> _isEnabled { 1 };

public:
    Book(ull num, ull value, const string& name)
        : Base(num, value, name)
    {
    }
    Book(ull num, ull value, const string& name, bool state)
        : Base(num, value, name)
    {
        _isEnabled[0] = state;
    }
    Book(const Book& book)
        : Base(book)
    {
        this->_isEnabled[0] = book._isEnabled[0];
    }
    Book(Book&& book)
        : Base(book)
    {
        this->_isEnabled[0] = book._isEnabled[0];
    }
    bool isEnabled() const
    {
        return this->_isEnabled[0];
    }
    auto flip(bool i) -> bool
    {
        return this->_isEnabled[0] = i;
    }
    ostream& println(ostream& out = cout, char end = '\n', char separator = '\t') const;
    friend ostream& operator<<(ostream&, const Book&);
    Book& operator=(const Book& b);
};
#endif //__BOOK_HPP__