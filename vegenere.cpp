#include <bits/stdc++.h>
using namespace std;

string encryptText(string text, string key) {
    string encrypt = "";
    int keyLen = key.length();
    int j = 0; // pointer for key

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            encrypt += ' '; // keep spaces as is
            continue;
        }

        char t = toupper(text[i]);
        char k = toupper(key[j % keyLen]);

        int shift = k - 'A';
        char c = ((t - 'A' + shift) % 26) + 'A';

        encrypt += c;
        j++; // only move key pointer for letters, not spaces
    }
    return encrypt;
}

string decryptText(string encrypt, string key) {
    string decrypt = "";
    int keyLen = key.length();
    int j = 0;

    for (int i = 0; i < encrypt.length(); i++) {
        if (encrypt[i] == ' ') {
            decrypt += ' ';
            continue;
        }

        char e = toupper(encrypt[i]);
        char k = toupper(key[j % keyLen]);

        int shift = k - 'A';
        char c = ((e - 'A' - shift + 26) % 26) + 'A';

        decrypt += tolower(c);
        j++;
    }
    return decrypt;
}

int main() {
    string text, key;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);
    getline(inFile, key);
    inFile.close();

    if (key.empty()) {
        cout << "Error: Key cannot be empty." << endl;
        return 1;
    }

    string encrypted = encryptText(text, key);
    string decrypted = decryptText(encrypted, key);

    cout << "Original Text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}