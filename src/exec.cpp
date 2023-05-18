#include "exec.hpp"
void db::createDB(type t)
{
    ui::printHeader();
    if (t == type::USER) {
        ui::printAt(ui::CENTER, "Load USER Database(.csv)");
        file::getPath(data::path);
        if (data::path == "-1")
            data::path = defaultUser;
        if (!file::openFile(data::fUser, data::path)) {
            cout << "Error Opening File: check permission or file not exist" << '\n';
            data::fUser.clear();
            return;
        }
        csv::read(data::fUser, data::memUser);
    } else {
        ui::printAt(ui::CENTER, "Load BOOK Database(.csv)");
        file::getPath(data::path);
        if (data::path == "-1")
            data::path = defaultBook;
        if (!file::openFile(data::fBook, data::path)) {
            cout << "Error Opening File: check permission or file not exist" << '\n';
            data::fBook.clear();
            return;
        }
        csv::read(data::fBook, data::memBook);
    }
}

void editDB(type t)
{
    short op, nums;
    while (true) {
        ui::printHeader();
        if (t == type::USER) {
            ui::printAt(ui::CENTER, "Edit USER Database");
            cout << '\n';
            cout << "1. List All Users" << '\n';
            cout << "2. Add a User" << '\n';
            cout << "3. Edit a User" << '\n';
            cout << "4. Load another Database" << '\n';
            cout << "5. Delete User(s)" << '\n';
            cout << "6. Save Database" << '\n';
            cout << "7. Go Back" << '\n';
            cout << "99. CLEAR MEMORY" << '\n';
            nums = 7;
        } else {
            ui::printAt(ui::CENTER, "Edit BOOK Database");
            cout << '\n';
            cout << "1. List All Sellable Books" << '\n';
            cout << "2. List All Books" << '\n';
            cout << "3. Add a Book" << '\n';
            cout << "4. (Un)Hide Book(s)" << '\n';
            cout << "5. Delete Book(s)" << '\n';
            cout << "6. Delete All Hidden Books" << '\n';
            cout << "7. Load another Database" << '\n';
            cout << "8. Save Database" << '\n';
            cout << "9. Go Back" << '\n';
            cout << "99. CLEAR MEMORY" << '\n';
            nums = 9;
        }
        cout << "Choose one operation[1-" << nums << ',' << 99 << "]:" << '\t';
        cin >> op;
        switch (op) {
        case 1:
            if (t == type::USER) {
                data::memUser.printHeader();
                data::memUser.printDB();
            } else {
                data::memBook.printSellable();
            }
            break;
        case 2:
            if (t == type::USER)
                db::add(data::memUser);
            else {
                data::memBook.printHeader();
                data::memBook.printDB();
            }
            break;
        case 3:
            if (t == type::USER)
                db::edit(data::memUser);
            else
                db::add(data::memBook);
            break;
        case 4:
            if (t == type::USER)
                db::createDB(USER);
            else
                db::hide(data::memBook);
            break;
        case 5:
            if (t == type::USER)
                db::del(data::memUser);
            else
                db::del(data::memBook);
            break;
        case 6:
            if (t == type::USER)
                db::save(data::fUser, data::memUser, type::USER);
            else
                cout << "Purged " << data::memBook.purge() << " Books\n";
            break;
        case 7:
            if (t == type::USER)
                return;
            else
                db::createDB(BOOK);
            break;
        case 8:
            if (t == type::BOOK)
                db::save(data::fBook, data::memBook, type::BOOK);
            else
                cout << InvaildChoice << '\n';
            break;
        case 9:
            if (t == type::BOOK)
                return;
            else
                cout << InvaildChoice << '\n';
        case 99:
            if (t == type::USER)
                db::clear(data::memUser);
            else
                db::clear(data::memBook);
            break;
        default:
            cout << InvaildChoice << '\n';
        }
    }
}
void checkout()
{
    ull tot;
    ull user, book, quant;
    string c;
    while (true) {
        ui::clear();
        ui::printHeader();
        ui::printAt(ui::CENTER, "Checkout");
        cout << '\n'
             << '\n';
        data::memBook.printSellable();
        cout << "Enter USERID BOOKID and Quantity(Split by SPACE):" << '\n';
        cin >> user >> book >> quant;
        if (user >= data::memUser.size() || book >= data::memBook.size()) {
            cout << "Out of Bound. Returning...";
            return;
        } else {
            tot = quant * data::memBook[book].getValue;
            cout << "Total: " << tot
                 << "(CNY)"
                 << " for " << quant << 'x' << ' '
                 << data::memBook[book].getName << '\n';
        }
        if (tot > data::memUser[user].getValue) {
            cout << "Insufficient Credit. Returning..." << '\n';
            return;
        } else {
            cout << "Pay?(Yes/anything else)" << '\t';
            cin >> c;
            if (c == "Yes") {
                data::memUser[user] -= tot;
                return;
            } else
                return;
        }
    }
}