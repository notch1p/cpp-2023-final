#pragma once
#include "csv.hpp"
#include "data.h"
#include "interface.hpp"

static const string defaultUser = "./users.csv";
static const string defaultBook = "./books.csv";
static const string InvaildChoice = "Invaild: Please choose again";
namespace db {
template <class T>
void save(fstream&, Database<T>&, type t);
void createDB(type t);
void loadDB(fstream&, Database<User>&);
}
void editDB(type t);
void checkout();
template <class T>
void db::save(fstream& fs, Database<T>& db, type t)
{
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "Saving Database as...");
    file::getPath(data::path);
    if (data::path == "-1") {
        if (t == type::USER) {
            data::path = defaultUser;
        } else {
            data::path = defaultBook;
        }
    }
    csv::dump(fs, db, data::path);
}
