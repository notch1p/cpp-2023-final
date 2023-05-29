#include "data.h"
#include "database.hpp"
#include "exec.hpp"
#include "interface.hpp"
#include <cstring>
inline void welcome()
{
    ui::printHeader();
    ui::printAt(ui::CENTER, "WELCOME");
    ui::printAt(ui::CENTER, "~library system by E. Gao~");
    ui::printHeader();
}

void which()
{
    while (true) {
        short op;
        ui::printHeader();
        ui::printAt(ui::CENTER, "Do Something...");
        cout << '\n';
        ui::printAt(ui::CENTER, "1. Edit USER");
        ui::printAt(ui::CENTER, "2. Edit BOOK");
        ui::printAt(ui::CENTER, "3. Checkout");
        ui::printAt(ui::CENTER, "4. Exit");

        cout << "Input:" << '\t';
        cin >> op;
        switch (op) {
        case 1:
            editDB(USER);
            break;
        case 2:
            editDB(BOOK);
            break;
        case 3:
            checkout();
            break;
        case 4:
            exit(0);
        default:
            cout << InvaildChoice << '\n';
        }
    }
}
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#if defined _WIN32
    system("chcp 65001");
#endif
    if (argc == 2) {
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            cout << "Usage: bookstore [args]" << '\n'
                 << '\n';
            cout << "Arguments:" << '\n';
            cout << "  -h --help" << '\n';
            cout << "\tshow help information" << '\n';
            cout << "  -u --user {path}" << '\n';
            cout << "\tload database into USER" << '\n';
            cout << "  -b --book {path}" << '\n';
            cout << "\tload database into BOOK" << '\n'
                 << '\n';
            exit(0);
        }
    } else if (argc > 2 && argc <= 5) {
        for (auto i = 1; i < argc - 1; i++) {
            if (!strcmp(argv[i], "-u") || !strcmp(argv[i], "--user")) {
                file::openFile(data::fUser, argv[i + 1]);
                // cout<<argv[i + 1]<<'\n';
                csv::read(data::fUser, data::memUser);
            }
            if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--book")) {
                file::openFile(data::fBook, argv[i + 1]);
                // cout<<argv[i + 1]<<'\n';
                csv::read(data::fBook, data::memBook);
            }
        }
        which();
    } else {
        welcome();
        which();
    }
}
