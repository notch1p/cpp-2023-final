#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <string>
typedef unsigned long long ull;
class Base {
private:
    ull num;
    ull value;
    std::string name;

public:
    Base()
        : num(0)
        , value(0)
    {
    }
    Base(ull num, ull value, const std::string& name)
        : num(num)
        , value(value)
        , name(name) {};
    Base(const Base& base)
        : num(base.num)
        , value(base.value)
        , name(base.name) {};
    Base(Base&& base)
        : num(std::move(base.num))
        , value(std::move(base.value))
        , name(std::move(base.name)) {};
    ~Base() = default;

    void setNum(ull num) { this->num = num; }
    void setValue(ull value) { this->value = value; }
    void setName(const std::string& name) { this->name = name; }
    const ull& getNum = num;
    const ull& getValue = value;
    const std::string& getName = name;
};
#endif //__BASE_HPP__