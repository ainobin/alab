#include <bits/stdc++.h>
using namespace std;

string encryptText(string text, int keyA, int keyB, string encrypt, vector<char> alp) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            encrypt += '#'; 
        } else {
            char a = toupper(text[i]);
            int ind = a - 65; 
            
            // Apply Affine encryption formula
            int ind_new = (keyA * ind + keyB) % 26; 
            encrypt += alp[ind_new]; 
        }
    }
    return encrypt;
}

string decryptText(string encrypt, int keyA, int keyB, string decrypt, vector<char> alp) {
    // Find the modular multiplicative inverse of keyA
    int inverse = 0;
    for (int j = 1; j < 26; j++) {
        if ((keyA * j) % 26 == 1) {
            inverse = j;
            break;
        }
    }

    for (int i = 0; i < encrypt.length(); i++) {
        if (encrypt[i] == '#') {
            decrypt += ' '; 
        } else {
            char a = encrypt[i];
            int ind = a - 65; 
            
            // Shift back by keyB (ensure positive by adding 26)
            int shifted = (ind - (keyB % 26) + 26) % 26;
            
            // Multiply by inverse to reverse keyA
            int ind_new = (inverse * shifted) % 26; 
            
            decrypt += tolower(alp[ind_new]); 
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
    int keyA, keyB;
    string encrypt = "";
    string decrypt = "";

    // Open the input file
    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }
    
    // File expects: Text on line 1, keyA on line 2, keyB on line 3
    getline(inFile, text);
    inFile >> keyA;
    inFile >> keyB;
    inFile.close();

    // Validate keyA
    if (__gcd(keyA, 26) != 1) {
        cout << "Error: Invalid Key A" << endl;
        return 1;
    }

    encrypt = encryptText(text, keyA, keyB, encrypt, alp);
    decrypt = decryptText(encrypt, keyA, keyB, decrypt, alp);
    
    cout << "Original Text: " << text << endl;
    cout << "Key A: " << keyA << endl;
    cout << "Key B: " << keyB << endl;
    cout << "Encrypted Text: " << encrypt << endl;
    cout << "Decrypted Text: " << decrypt << endl;

    return 0;
}