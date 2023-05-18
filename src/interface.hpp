#pragma once
#include "database.hpp"
#include <iostream>
#include <sstream>
#include <string>
namespace ui {
enum Position { LEFT,
    CENTER,
    RIGHT };
void printAt(Position pos, std::string s, int width = 80);
void printHeader(char ch = '=', int width = 80);
void clear();
}
namespace file {
void getPath(std::string&);
bool openFile(std::fstream&, std::string&);
bool openFile(std::fstream&, const char*);
bool saveFile(std::fstream&, std::string&);
}

namespace db {
void add(Database<Book>&);
void add(Database<User>&);
void edit(Database<Book>&);
void edit(Database<User>&);
void hide(Database<Book>&);

template <class T>
void clear(Database<T>& db)
{
    char cond;
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "EVERYTHING in regard to the databases shall be cleared.");
    cout << "Continue?(Y/anything else)" << '\t';
    cin >> cond;
    if (cond == 'Y')
        db.clear();
}
template <class T>
void del(Database<T>& db)
{
    string s;
    stringstream ss;
    vector<ull> pos;
    ull n;
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "Deleting...");
    cout << "Input by ID(Split by SPACE):" << '\n';
    getline(std::cin, s);
    ss << s;
    while (ss >> n) {
        pos.push_back(n);
    }
    for (const auto& i : pos) {
        if (i < db.size())
            db.purge(i);
        else
            cout << "Omitting out of range ID " << i << '\n';
    }
    cout << "Delete Succeed" << '\n';
}
}

enum type {
    USER,
    BOOK
};