#include <bits/stdc++.h>
using namespace std;

const int N = 30;
char table_key[N][N], table_row[N], table_col[N];

void create_table_key(const string& key) {
	int temp = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			char c = key[temp++];
			table_key[i][j] = c;
			table_row[c-'A'] = i;
			table_col[c-'A'] = j;
		}
		table_key[i][5] = table_key[i][0];
	}

	for (int i = 0; i < 5; ++i) {
		table_key[5][i] = table_key[0][i];
	}
}

string generate_key(const string& key) {
	bool char_used[N];
	string result;

	for (int i = 0; i < key.size(); ++i) {
		assert(key[i] >= 'A' && key[i] <= 'Z');
		if ((key[i] != 'J') && (!char_used[key[i]-'A'])) {
			result += key[i];
			char_used[key[i]-'A'] = 1;
		}
	}

	for (char c = 'A'; c <= 'Z'; ++c)
		if ((!char_used[c-'A']) && (c != 'J'))
			result += c;

	return result;
}

bool is_same_row(char c1, char c2) {
	return table_row[c1-'A'] == table_row[c2-'A'];
}

bool is_same_column(char c1, char c2) {
	return table_col[c1-'A'] == table_col[c2-'A'];
}

string choose_char_on_right(char c1, char c2) {
	string result;
	int r, c;

	r = table_row[c1-'A'];
	c = table_col[c1-'A'];
	result += table_key[r][(c+1)%5];

	r = table_row[c2-'A'];
	c = table_col[c2-'A'];
	result += table_key[r][(c+1)%5];

	return result;
}

string choose_char_on_left(char c1, char c2) {
	string result;
	int r, c;

	r = table_row[c1-'A'];
	c = table_col[c1-'A'];
	result += table_key[r][(c+4)%5];

	r = table_row[c2-'A'];
	c = table_col[c2-'A'];
	result += table_key[r][(c+4)%5];

	return result;
}

string choose_char_on_top(char c1, char c2) {
	string result;
	int r, c;

	r = table_row[c1-'A'];
	c = table_col[c1-'A'];
	result += table_key[(r+4)%5][c];

	r = table_row[c2-'A'];
	c = table_col[c2-'A'];
	result += table_key[(r+4)%5][c];

	return result;
}

string choose_char_on_bottom(char c1, char c2) {
	string result;
	int r, c;

	r = table_row[c1-'A'];
	c = table_col[c1-'A'];
	result += table_key[(r+1)%5][c];

	r = table_row[c2-'A'];
	c = table_col[c2-'A'];
	result += table_key[(r+1)%5][c];

	return result;
}

string choose_char_square(char c1, char c2) {
	string result;
	result += table_key[table_row[c1-'A']][table_col[c2-'A']];
	result += table_key[table_row[c2-'A']][table_col[c1-'A']];
	return result;
}

string choose_char_encrypt(char c1, char c2) {
	if (is_same_row(c1, c2)) return choose_char_on_right(c1, c2);
	if (is_same_column(c1, c2)) return choose_char_on_bottom(c1, c2);
	return choose_char_square(c1, c2);
}

string choose_char_decrypt(char c1, char c2) {
	if (is_same_row(c1, c2)) return choose_char_on_left(c1, c2);
	if (is_same_column(c1, c2)) return choose_char_on_top(c1, c2);
	return choose_char_square(c1, c2);
}

string encrypt(const string& plain) {
	string cipher, space;
	char last_c = 0;
	for (int i = 0; i < plain.size(); ++i) {
		char c = plain[i];
		if (c >= 'A' && c <= 'Z') {
			if (c == 'J') c = 'I';
			if (last_c) {
				char cur_c = (last_c == c) ? 'Z' : c;
				string c_cipher = choose_char_encrypt(last_c, cur_c);
				cipher += c_cipher[0];
				cipher += space;
				cipher += c_cipher[1];

				last_c = (last_c == c) ? c : 0;
				space.clear();
			}
			else last_c = c;
		}
		else if (!last_c) cipher += c;
		else space += c;
	}
	if (last_c) cipher += choose_char_encrypt(last_c, 'Z');

	return cipher;
}

string decrypt(const string& cipher) {
	string plain, space;
	char last_c = 0;
	for (int i = 0; i < cipher.size(); ++i) {
		char c = cipher[i];
		if (c >= 'A' && c <= 'Z') {
			if (last_c) {
				string c_plain = choose_char_decrypt(last_c, c);
				plain += c_plain[0];
				plain += space;
				plain += c_plain[1];

				last_c = 0;
				space.clear();
			}
			else last_c = c;
		}
		else if (!last_c) plain += c;
		else space += c;
	}
	assert(last_c == 0);

	return plain;
}

void do_encrypt() {
	string plain, cipher, key;

	cout << "Plain : ";
	getline(cin,plain);

	cout << "Key : ";
	cin >> key;

	create_table_key(generate_key(key));

	string result = encrypt(plain);
	cout << "Cipher : " << endl;

	cout << "==== Apa Adanya : ";
	cout << result << endl;

	string tanpa_spasi;
	for (int i = 0; i < result.size(); ++i)
		if (result[i] != ' ') tanpa_spasi += result[i];
	cout << "==== Tanpa Spasi : " << tanpa_spasi << endl;

	cout << "==== Kelompok 5 huruf : ";
	for (int i = 0; i < tanpa_spasi.size(); i += 5) {
		cout << tanpa_spasi.substr(i, 5);
		cout << (i + 5 >= tanpa_spasi.size() ? '\n' : ' ');
	}

	cout << "Plain again = " << decrypt(encrypt(plain)) << endl;
}

void do_decrypt() {
	string plain, cipher, key;

	cout << "Cipher : ";
	getline(cin, cipher);

	cout << "Key : ";
	cin >> key;

	create_table_key(generate_key(key));

	cout << "Plain : " << endl;

	string result = decrypt(cipher);

	cout << "==== Tanpa Spasi : " << result << endl;
}

void menu() {
    cout << "Playfair\n";
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