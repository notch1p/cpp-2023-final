#include "user.hpp"
#include <iostream>

ostream& User::println(ostream& out, char end, char separator) const
{
    out << this->getNum << separator << this->getName << separator
        << this->getValue << end;
    return out;
}

ostream& operator<<(ostream& out, const User& user)
{
    return user.println(out);
}

bool User::operator==(const User& user)
{
    return (this->getName == user.getName
        && this->getNum == user.getNum
        && this->getValue == user.getValue);
}

User& User::operator=(const User& b)
{
    this->setName(b.getName);
    this->setNum(b.getNum);
    this->setValue(b.getValue);
    return *this;
}
User& User::operator-=(ull t)
{
    this->setValue(this->getValue - t);
    return *this;
}