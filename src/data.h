#pragma once
#include "database.hpp"
#include <fstream>
#include <string>

namespace data {
static Database<User> memUser;
static Database<Book> memBook;
static fstream fUser, fBook;
static string path;
}