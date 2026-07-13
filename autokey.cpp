#include <bits/stdc++.h>
using namespace std;

string encryptText(string text, int key, string encrypt, vector<char> alp) {
    int new_key = key; // Starts with the initial integer key

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            encrypt += '#'; 
        } else {
            char a = toupper(text[i]);
            int ind = a - 65; 
            
            // Apply the cipher formula with the running key
            int ind_new = (ind + new_key) % 26; 
            encrypt += alp[ind_new]; 
            
            // Autokey step: The plaintext index becomes the key for the next letter
            new_key = ind; 
        }
    }
    return encrypt;
}

string decryptText(string encrypt, int key, string decrypt, vector<char> alp) {
    int new_key = key;

    for (int i = 0; i < encrypt.length(); i++) {
        if (encrypt[i] == '#') {
            decrypt += ' '; 
        } else {
            char a = encrypt[i];
            int ind = a - 65; 
            
            // Reverse the cipher formula
            int ind_old = (ind - new_key + 26) % 26; 
            decrypt += tolower(alp[ind_old]); 
            
            // Autokey step: The decrypted index becomes the key for the next letter
            new_key = ind_old; 
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