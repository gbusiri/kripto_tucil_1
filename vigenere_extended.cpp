#include <bits/stdc++.h>
#include "util.h"

using namespace std;

string encrypt(const string& plain, const string& key) {
    string cipher; cipher.resize(plain.size());
    for (unsigned long long i = 0; i < plain.size(); ++i) {
        cipher[i] = plain[i]+key[i%key.size()];
    }
    return cipher;
}

string decrypt(const string& cipher, const string& key) {
    string plain; plain.resize(cipher.size());
    for (unsigned long long i = 0; i < cipher.size(); ++i) {
        plain[i] = cipher[i]-key[i%key.size()];
    }
    return plain;
}

void do_encrypt() {
    string plain = get_input();
    string key = get_key();
    string cipher = encrypt(plain, key);

    cout << "\n";
    cout << "Plain:\n";
    cout << plain << endl;

    cout << "\n";
    cout << "Cipher (Apa Adanya):\n";
    cout << cipher << endl;

    cout << "Cipher (Tanpa Spasi):\n";
    string tanpa_spasi;
    for (int i = 0; i < cipher.size(); ++i) {
        if (cipher[i] == ' ') continue;
        tanpa_spasi += cipher[i];
    }
    cout << tanpa_spasi << "\n";

    cout << "Cipher (Kelompok 5 Huruf):\n";
    for (int i = 0; i < tanpa_spasi.size(); i += 5) {
        if (i) cout << ' ';
        cout << tanpa_spasi.substr(i, 5);
    }
    cout << "\n";

    const string file_name = "cipher.txt";
    ofstream f(file_name.c_str(), ios::out|ios::binary);
    f << cipher;
    f.close();

    cout << "\n";
    cout << "Ciphertext tersimpan dalam file " << file_name << endl;
}

void do_decrypt() {
    string cipher = get_input();
    string key = get_key();
    string plain = decrypt(cipher, key);

    cout << "\n";
    cout << "Cipher:\n";
    cout << cipher << endl;

    cout << "\n";
    cout << "Plain:\n";
    cout << plain << endl;

    const string file_name = "plain.txt";
    ofstream f(file_name.c_str(), ios::out|ios::binary);
    f << plain;
    f.close();

    cout << "\n";
    cout << "Plaintext tersimpan dalam file " << file_name << endl;
}

void menu() {
    cout << "Vigenere Cipher Extended\n";
    while (1) {
        cout << "\nPilihan menu:\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "0. Keluar\n";
        cout << "> ";
        int menu; cin >> menu;
        char c; cin.get(c); // ignore newline
        if (menu == 0) break;
        switch (menu) {
            case 1:
                do_encrypt();
                break;
            case 2:
                do_decrypt();
                break;
            default:
                cout << "Pilihan salah!\n";
        }
    }
}

int main() {
    menu();
    return 0;
}