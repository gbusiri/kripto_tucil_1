#include <bits/stdc++.h>
using namespace std;

const int N = 30;
char table_key[N][N];
int is_alphabet_use[N];

void create_table_key(string key) {
	int temp = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			table_key[i][j] = key[temp++];
		}

		table_key[i][5] = table_key[i][0];
	}

	for (int i = 0; i < 5; ++i)
	{
		table_key[5][i] = table_key[0][i];
	}
}

string generate_key(string key) {
	string result = "";
	memset(is_alphabet_use, 0, sizeof is_alphabet_use);
	for (int i = 0; i < key.size(); ++i)
	{
		if ((key[i] != 'J') && (!is_alphabet_use[key[i]-'A'])) {
			result += key[i];
			is_alphabet_use[key[i]-'A'] = 1;
		}
	}

	for (int i = 0; i < 26; ++i)
	{
		if ((!is_alphabet_use[i]) && (i != 9)) {
			result += 'A'+i;
		}
	}

	return result;
}

bool is_same_row(char c1, char c2) {
	int row1, row2;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c1)
				row1 = i;

			if (table_key[i][j] == c2)
				row2 = i;
		}
	}

	if (row1 == row2)
		return true;
	else
		return false;
}

bool is_same_column(char c1, char c2) {
	int column1, column2;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c1)
				column1 = j;

			if (table_key[i][j] == c2)
				column2 = j;
		}
	}

	if (column1 == column2)
		return true;
	else
		return false;
}

string choose_char_on_right(char c1, char c2) {
	string result = "";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c1) {
				result += table_key[i][j+1];
				break;
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c2) {
				result += table_key[i][j+1];
				break;
			}
		}
	}

	// cout << "rgh = " << c1 << " " << c2 << endl;
	return result;
}

string choose_char_on_left(char c1, char c2) {
	string result = "";
	for (int i = 4; i >= 0; --i)
	{
		for (int j = 5; j >= 1; --j)
		{
			if (table_key[i][j] == c1) {
				result += table_key[i][j-1];
				break;
			}
		}
	}

	for (int i = 4; i >= 0; --i)
	{
		for (int j = 5; j >= 1; --j)
		{
			if (table_key[i][j] == c2) {
				result += table_key[i][j-1];
				break;
			}
		}
	}
	//cout << "left = " << result << endl;
	return result;
}

string choose_char_on_top(char c1, char c2) {
	string result = "";
	for (int i = 5; i >= 1; --i)
	{
		for (int j = 4; j >= 0; --j)
		{
			if (table_key[i][j] == c1) {
				result += table_key[i-1][j];
				break;
			}
		}
	}

	for (int i = 4; i >= 0; --i)
	{
		for (int j = 4; j >= 0; --j)
		{
			if (table_key[i][j] == c2) {
				result += table_key[i-1][j];
				break;
			}
		}
	}
	//cout << "top = " << result << endl;
	return result;
}

string choose_char_on_bottom(char c1, char c2) {
	string result = "";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c1) {
				result += table_key[i+1][j];
				break;
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c2) {
				result += table_key[i+1][j];
				break;
			}
		}
	}

	// cout << "bot = " << c1 <<  " " << c2 << endl;
	return result;
}

string choose_char_square(char c1, char c2) {
	string result = "";
	int row1, row2, column1, column2;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c1) {
				row1 = i;
				column1 = j;
				break;
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (table_key[i][j] == c2) {
				row2 = i;
				column2 = j;
				break;
			}
		}
	}

	result += table_key[row1][column2];
	result += table_key[row2][column1];

	// cout << "squ = " << c1 << " " << c2 << endl;
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