#include "csv.hpp"
using namespace std;
void csv::read(fstream& csv, Database<Book>& db)
{
    db.clear();
    ull cnt = 0;
    string t, word;
    vector<string> words;
    while (getline(csv, t)) {
        words.clear();
        stringstream s(t);
        while (getline(s, word, ',')) {
            words.push_back(word);
        }
        ull value = strtoull(words[2].c_str(), nullptr, 10);
        auto flag = [&]() -> bool { return words[3] == "False" ? 0 : 1; };
        db.emplace_back(value, words[1], (words[3] == "False" ? 0 : 1));
        cnt++;
    }
    std::cout << "Loaded BOOK database" << '\n';
    csv.close();
}

void csv::read(fstream& csv, Database<User>& db)
{
    db.clear();
    string t, word;
    vector<string> words;
    while (getline(csv, t)) {
        words.clear();
        stringstream s(t);
        while (getline(s, word, ',')) {
            words.push_back(word);
        }
        ull value = strtoull(words[2].c_str(), nullptr, 10);
        db.emplace_back(value, words[1]);
    }
    std::cout << "Loaded USER database" << '\n';
    csv.close();
}