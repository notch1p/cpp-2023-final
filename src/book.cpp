#include "book.hpp"
#include <iostream>

ostream& Book::println(ostream& out, char end, char separator) const
{
    out << this->getNum << separator
        << this->getName << separator
        << this->getValue << separator
        << (this->isEnabled()
                   ? "True"
                   : "False")
        << end;
    return out;
}
ostream& operator<<(ostream& out, const Book& book)
{
    return book.println(out);
}

Book& Book::operator=(const Book& b)
{
    this->setName(b.getName);
    this->setNum(b.getNum);
    this->setValue(b.getValue);
    this->flip(b.isEnabled());
    return *this;
}