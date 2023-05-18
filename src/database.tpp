#pragma once
template <class T>
T& Database<T>::operator[](ull pos)
{
    return arr[pos];
}
template <class T>
inline void Database<T>::printDB()
{
    for (auto i = arr.begin(); i != arr.end(); i++) {
        i->println();
        cout << string(80, '-') << '\n';
    }
}
template <>
inline void Database<Book>::printSellable()
{
    cout << "ID" << '\t'
         << "Name" << '\t'
         << "Price" << '\n';
    for (auto i = arr.begin(); i != arr.end(); i++) {
        if (i->isEnabled()) {
            cout << i->getNum << '\t'
                 << i->getName << '\t'
                 << i->getValue << '\n';
            cout << string(80, '-') << '\n';
        }
    }
}
template<class T> inline void Database<T>::updateID(){
    for(auto i = 0; i < arr.size(); i++){
        arr[i].setNum(i);
    }
}
template <>
inline void Database<Book>::printHeader()
{
    cout << '\n'
         << '\n';
    cout << "ID" << '\t'
         << "Name" << '\t'
         << "Price" << '\t'
         << "Selling?" << '\n';
}
template <>
inline void Database<User>::printHeader()
{
    cout << '\n'
         << '\n';
    cout << "ID" << '\t'
         << "Name" << '\t'
         << "Credit(CNY)" << '\n';
}
template <>
inline void Database<Book>::hide(ull pos)
{
    arr[pos].flip(false);
}
template <>
inline void Database<Book>::restore(ull pos)
{
    arr[pos].flip(true);
}
template <>
inline ull Database<Book>::purge()
{
    ull cnt = 0;
    for (ull i = 0; i < arr.size(); i++) {
        if (!arr[i].isEnabled()) {
            cnt++;
            arr.erase(arr.begin() + i);
        }
    }
    this->updateID();
    return cnt;
}
