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
	memset(is_alphabet_use, 0, N);
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

string divided_plain(string plain_full) {
	string result = "";
	string plain = "";
	for (int i = 0; i < plain_full.size(); ++i)
	{
		if (plain_full[i] != ' ') {
			plain += plain_full[i];
		}
	}

	int i = 0;
	while (i < plain.size()) {
		if (plain.size() - i == 1) {
			if (plain[i] == 'J') {
				result += "I";
			}
			else {
				result += plain[i];
			}

			result += "Z";
			i++;
		}
		else {
			string temp = plain.substr(i, 2);
			if ((temp[0] != 'J') && (temp[1] != 'J')) {
				if (temp[0] == temp[1]) {
					result += temp[0];
					result += "Z";
					i++;
				}
				else {
					result += temp;
					i += 2;
				}
			}
			else {
				if (temp[0] == temp[1]) {
					result += "IZ";
					i++;
				}
				else {
					if (temp[0] == 'J') {
						result += "I";
						result += temp[1];
					}
					else if (temp[1] == 'J') {
						result += temp[0];
						result += "I";
					}
					i += 2;
				}
			}
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
				column2 = j;

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
	for (int i = 5; i >= 1; --i)
	{
		for (int j = 5; j >= 1; --j)
		{
			if (table_key[i][j] == c1) {
				result += table_key[i][j-1];
				break;
			}
		}
	}

	for (int i = 5; i >= 1; --i)
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

string encrypt(string plain) {
	string cipher = "";
	for (int i = 0; i < plain.size(); i+=2)
	{
		string temp = plain.substr(i, 2);
		if (is_same_row(temp[0], temp[1])) {
			cipher += choose_char_on_right(temp[0], temp[1]);
		}
		else if (is_same_column(temp[0], temp[1])) {
			cipher += choose_char_on_bottom(temp[0], temp[1]);
		}
		else {
			cipher += choose_char_square(temp[0], temp[1]);
		}
	}

	return cipher;
}

string decrypt(string cipher) {
	string plain = "";
	for (int i = 0; i < cipher.size(); i+=2)
	{
		string temp = cipher.substr(i, 2);
		if (is_same_row(temp[0], temp[1])) {
			plain += choose_char_on_left(temp[0], temp[1]);
		}
		else if (is_same_column(temp[0], temp[1])) {
			plain += choose_char_on_top(temp[0], temp[1]);
		}
		else {
			plain += choose_char_square(temp[0], temp[1]);
		}
	}

	return plain;
}

void do_encrypt() {
	string plain, cipher, key;

	cout << "Plain : ";
	getline(cin,plain);

	cout << "Key : ";
	cin >> key;

	create_table_key(generate_key(key));

	cout << "Cipher : " << endl;

	string result = encrypt(divided_plain(plain));

	//MASIH NGACO
	cout << "==== Apa Adanya : ";
	string result_apa_adanya = "";
	for (int i = 0; i < result.size(); ++i)
	{
		if (plain[i] == ' ') {
			result_apa_adanya += ' ';
			result_apa_adanya += result[i];
		}
		else {
			result_apa_adanya += result[i];
		}
	}
	cout << result_apa_adanya << endl;

	cout << "==== Tanpa Spasi : " << result << endl;
	cout << "==== Kelompok 5 huruf : ";
	string result_5_group = "";
	for (int i = 0; i < result.size(); i+=5)
	{
		result_5_group += result.substr(i, 5);
		result_5_group += " ";
	}
	cout << result_5_group << endl;
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