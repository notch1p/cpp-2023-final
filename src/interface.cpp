#include "interface.hpp"
using namespace std;

void ui::printAt(Position pos, std::string s, int width)
{
    int spaces = 0;
    switch (pos) {
    case CENTER:
        spaces = (width - s.size()) / 2;
        break;
    case RIGHT:
        spaces = width - s.size();
        break;
    default:
        break;
    }
    if (spaces > 0)
        cout << string(spaces, ' ');
    cout << s << '\n';
}
void ui::printHeader(char ch, int width)
{
    cout << string(width, ch) << '\n';
}
void ui::clear()
{
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

void file::getPath(string& path)
{
    cout << "input path:(enter -1 for default path)\n";
    cout << "!!use '/' instead of '\\' on Windows!!\n";
    path.clear();
    cin.ignore();
    getline(std::cin, path);
}
bool file::openFile(fstream& fs, string& path)
{
    fs.open(path, fstream::in);
    return !fs.fail();
}
bool file::openFile(fstream& fs, const char* path){
    fs.open(path,fstream::in);
    return !fs.fail();
}
bool file::saveFile(fstream& fs, string& path){
    fs.open(path,fstream::out);
    return !fs.fail();
}
void db::add(Database<Book>& db)
{
    ui::clear();
    ull p = 0;
    string s;
    ui::printHeader();
    ui::printAt(ui::CENTER, "Add a book");
    std::cin.ignore();
    cout << "Enter Bookname:" << '\n';
    getline(std::cin, s);
    cout << "Enter Price:" << '\n';
    std::cin >> p;
    db.emplace_back(p, s);
}
void db::add(Database<User>& db)
{
    ui::clear();
    ull p = 0;
    string s;
    ui::printHeader();
    ui::printAt(ui::CENTER, "Add a user");
    std::cin.ignore();
    cout << "Enter Username:" << '\n';
    getline(std::cin, s);
    cout << "Enter Credit:" << '\n';
    std::cin >> p;
    db.emplace_back(p, s);
}
void db::edit(Database<Book>& db)
{
    ull p = 0, pp, val;
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "Edit a book");
    db.printDB();
    cout << "Chose one by ID to edit:" << '\t';
    std::cin >> p;
    if (p >= db.size()) {
        cout << "Out of Bounds. Returning..." << '\n';
        return;
    } else {
        cout << "Found book with ID " << p << '\n';
        string s;
        pp = 0, val = 0;
        db[p].println();
        cout << "Actions: 1. Edit Name; 2. Edit Price; >=3. Go Back" << '\n';
        cout << "Choose one action:" << '\t';
        std::cin >> pp;
        switch (pp) {
        case 1:
            cout << "Input Name:" << '\n';
            std::cin >> s;
            db[p].setName(s);
            break;
        case 2:
            cout << "Input Price" << '\t';
            std::cin >> val;
            db[p].setValue(val);
            break;
        default:
            return;
        }
    }
}
void db::edit(Database<User>& db)
{
    ull p = 0, pp, val;
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "Edit a user");
    db.printDB();
    cout << "Chose one by ID to edit:" << '\t';
    std::cin >> p;
    if (p >= db.size()) {
        cout << "Out of Bounds. Returning..." << '\n';
        return;
    } else {
        cout << "Found user with ID " << p << '\n';
        string s;
        pp = 0, val = 0;
        db[p].println();
        cout << "Actions: 1. Edit Name; 2. Edit Credit; >=3. Go Back" << '\n';
        cout << "Choose one action:" << '\t';
        std::cin >> pp;
        switch (pp) {
        case 1:
            cout << "Input Name:" << '\n';
            std::cin >> s;
            db[p].setName(s);
            break;
        case 2:
            cout << "Input Credit" << '\t';
            std::cin >> val;
            db[p].setValue(val);
            break;
        default:
            return;
        }
    }
}
void db::hide(Database<Book>& db)
{
    std::string s, ss;
    stringstream temp;
    ull n, op;
    vector<ull> pos;
    ui::clear();
    ui::printHeader();
    ui::printAt(ui::CENTER, "(Un)Hide Books");
    cout << "Actions: 1.Hide Books; 2. Restore Books >=3. Go Back" << '\t';
    std::cin >> op;
    switch (op) {
    case 1:
        cout << "Input ID (Split by SPACE):" << '\n';
        cin.ignore();
        getline(std::cin, s);
        temp << s;
        while (temp >> n) {
            pos.push_back(n);
        }
        for (const auto& i : pos) {
            if (i < db.size())
                db.hide(i);
            else
                cout << "Omitting out of range ID:" << i << '\n';
        }
        break;
    case 2:
        cout << "Input ID (Split by SPACE):" << '\n';
        cin.ignore();
        getline(std::cin, s);
        
        temp << s;
        while (temp >> n) {
            pos.push_back(n);
        }
        for (const auto& i : pos) {
            if (i < db.size())
                db.restore(i);
            else
                cout << "Omitting out of range ID:" << i << '\n';
        }
        break;
    default:
        return;
    }
}