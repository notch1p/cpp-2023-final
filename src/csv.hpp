#pragma once
#include "data.h"
#include "database.hpp"
#include "interface.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static inline void addBom(fstream& csv)
{
    csv << "\xef\xbb\xbf";
}
namespace csv {
void read(std::fstream&, Database<Book>&);
void read(std::fstream&, Database<User>&);
template <class T>
inline void dump(fstream& csv, Database<T>& db, string& path, bool bom = true)
{
    if (!file::saveFile(csv, path)) {
        cout << "Error Creating File: check permission or invailed chars in path" << '\n';
        csv.clear();
        return;
    }
    if (bom)
        addBom(csv);
    for (auto i = db.begin(); i != db.end(); i++) {
        i->println(csv, '\n', ',');
    }
    ui::printAt(ui::CENTER, "Save Succeed");
    csv.close();
}
}