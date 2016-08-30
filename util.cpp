#include "util.h"

using namespace std;

string get_input() {
    int input_type = 0;
    while (!input_type) {
        cout << "\nTipe masukan:\n";
        cout << "1. File\n";
        cout << "2. Standard Input\n";
        cout << "> ";
        cin >> input_type;
        char c; cin.get(c); // ignore newline
        switch (input_type) {
            case 1:
            case 2:
                break;
            default:
                cout << "Pilihan salah!\n";
                input_type = 0;
        }
    }
    string s;
    switch (input_type) {
        case 2:
            cout << "\nInput:\n> ";
            getline(cin, s);
            break;
        case 1:
            while (1) {
                cout << "\nNama file:\n> ";
                string name; getline(cin, name);
                ifstream f(name.c_str(), ios::in|ios::binary|ios::ate);
                if (f.good() && f.tellg()) {
                    s.resize(f.tellg());
                    f.seekg(0, ios::beg);
                    f.read(&s[0], s.size());
                    f.close();
                    break;
                }
                else cout << "File tidak dapat dibuka!\n";
            }
    }
    return s;
}

string get_key() {
    cout << "\nKunci:\n> ";
    string key; getline(cin, key);
    return key;
}