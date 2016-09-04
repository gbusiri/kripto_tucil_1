#include <bits/stdc++.h>
#include "util.h"
using namespace std;

const int N = 30;
char table_alphabet[N];

void instance_table() {
	for (int i = 0; i < 26; ++i)
	{
		table_alphabet[i] = 'A'+i;
	}
}

bool isAlphabet(char s) {
	for (int i = 0; i < 26; ++i)
	{
		if (table_alphabet[i] == s) {
			return true;
		}
	}

	return false;
}

string encrypt(string plain, string key) {
	string cipher = "";
	int temp;

	for (int i = 0; i < plain.size(); ++i)
	{	
		if (isAlphabet(plain[i])) {
			temp = (plain[i]+key[i%key.size()]) % 26;
			cipher += table_alphabet[temp];
		}
		else {
			cipher += plain[i];
		}
	}

	return cipher;
}

string decrypt(string cipher, string key) {
	string plain = "";
	int temp;
	
	for (int i = 0; i < cipher.size(); ++i)
	{	
		if (isAlphabet(cipher[i])) {
			temp = (cipher[i]-key[i%key.size()]+26) % 26;
			plain += table_alphabet[temp];
		}
		else {
			plain += cipher[i];
		}
		
	}

	return plain;
}

void do_encrypt() {
    string plain = get_input();
    string key = get_key();
    instance_table();
    string cipher = encrypt(plain, key);

    cout << "==== Apa Adanya : ";
	cout << cipher << endl;

	string tanpa_spasi;
	for (int i = 0; i < cipher.size(); ++i)
		if (cipher[i] != ' ') tanpa_spasi += cipher[i];
	cout << "==== Tanpa Spasi : " << tanpa_spasi << endl;

	cout << "==== Kelompok 5 huruf : ";
	for (int i = 0; i < tanpa_spasi.size(); i += 5) {
		cout << tanpa_spasi.substr(i, 5);
		cout << (i + 5 >= tanpa_spasi.size() ? '\n' : ' ');
	}

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
    instance_table();
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
    cout << "Vigenere Cipher Standard\n";
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