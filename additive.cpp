// additive cipher
// input.txt file should contain the text to be encrypted and the key in the following format:
// hello world
// 19


#include <bits/stdc++.h>
using namespace std;

string encryptText(string text, int key, string encrypt, vector<char> alp) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            encrypt += '#'; // Use '#' to represent space in the encrypted text
        } else {
            char a = toupper(text[i]);
            int ind = a - 65; // Get the index of the character in the alphabet
            
            int ind_new = (ind + key) % 26; // Apply the additive cipher formula
            encrypt += alp[ind_new]; // Append the encrypted character
        }
    }

    return encrypt;
}

string decryptText(string encrypt, int key, string decrypt, vector<char> alp) {
    for (int i = 0; i < encrypt.length(); i++) {
        if (encrypt[i] == '#') {
            decrypt += ' '; // Convert '#' back to space in the decrypted text
        } else {
            char a = encrypt[i];
            int ind = a - 65; // Get the index of the character in the alphabet
            
            int ind_new = (ind - key + 26) % 26; // Apply the reverse additive cipher formula
            decrypt += tolower(alp[ind_new]); // Append the decrypted character
        }
    }

    return decrypt;
}

int main() {

    vector<char> alp;
    for (int i = 0; i < 26; i++) {
        alp.push_back((char)(i + 65)); 
    }

    string text;
    int key;
    string encrypt = "";
    string decrypt = "";

    // Open the input file
    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }
    
    getline(inFile, text);
    inFile >> key;
    inFile.close();

    key = key % 26;

    encrypt = encryptText(text, key, encrypt, alp);
    decrypt = decryptText(encrypt, key, decrypt, alp);
    

    cout << "Original Text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted Text: " << encrypt << endl;
    cout << "Decrypted Text: " << decrypt << endl;

    return 0;
}