#include <bits/stdc++.h>
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

int main() {
	string plain, key, cipher, cipher_non_space = "", cipher_five = "";
	int * lengthOfBytesFile;
	ofstream file, file_plain, file_cipher;

	instance_table();

	cout << "Plain : ";
	getline(cin, plain);

	cout << "Key : ";
	cin >> key;

	file.open("output.txt");
	cout << "Cipher : " << endl;

	cipher = encrypt(plain, key);
	cout << "==== Apa adanya : " << cipher << endl;
	file << "==== Apa adanya : " << cipher << endl;
	cout << "==== Tanpa spasi : ";
	file << "==== Tanpa spasi : ";
	for (int i = 0; i < cipher.size(); ++i)
	{
		if (isAlphabet(cipher[i])) {
			cipher_non_space += cipher[i];
		}
	}
	cout << cipher_non_space << endl;
	file << cipher_non_space + "\n";

	cout << "==== Kelompok 5 huruf : ";
	file << "==== Kelompok 5 huruf : ";
	for (int i = 0; i < cipher_non_space.size(); i+=5)
	{
		cipher_five += cipher_non_space.substr(i, 5) + " ";
	}
	cout << cipher_five << endl;
	file << cipher_five + "\n";
	file.close();
	cout << "Plain Again From Cipher = " << decrypt(cipher, key) << endl;

	return 0;
}