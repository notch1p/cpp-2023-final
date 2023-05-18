#pragma once
#include "book.hpp"
#include "user.hpp"
#include <fstream>
#include <iterator>
#include <vector>
typedef unsigned long long ull;

template <class T>
class Database {
private:
    std::vector<T> arr;

public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    auto begin() -> iterator { return arr.begin(); }
    const_iterator begin() const { return arr.begin(); }
    const_iterator cbegin() const { return arr.cbegin(); }
    auto end() -> iterator { return arr.end(); }
    const_iterator end() const { return arr.end(); }
    const_iterator cend() const { return arr.cend(); }

    template <typename... Args>
    void emplace_back(Args... args)
    {
        arr.emplace_back(arr.size(), args...);
    }
    T& operator[](ull);
    void purge(ull pos) { arr.erase(arr.begin() + pos); this->updateID();}
    ull purge();
    void hide(ull);
    void restore(ull);
    void printDB();
    void printHeader();
    void printSellable();
    void updateID();
    void clear() { arr.clear(); }
    size_t size()
    {
        return this->arr.size();
    }
};

#include "database.tpp"