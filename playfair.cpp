#include <bits/stdc++.h>
using namespace std;

// Simple helper to find the row and col of a letter in the 5x5 grid
void findPos(char matrix[5][5], char ch, int &row, int &col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encryptText(string text, char matrix[5][5], string encrypt) {
    string word = "";
    text += " "; // dummy space

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            if (word.length() > 0) {
                string prep = "";
                for(int j = 0; j < word.length(); j++) {
                    prep += word[j];
                    if (j + 1 < word.length() && word[j] == word[j+1]) prep += 'X';
                }
                if (prep.length() % 2 != 0) prep += 'X';

                // Encrypt in pairs using 2D matrix
                for(int j = 0; j < prep.length(); j += 2) {
                    int r1, c1, r2, c2;
                    findPos(matrix, prep[j], r1, c1);
                    findPos(matrix, prep[j+1], r2, c2);

                    if (r1 == r2) { // Same Row
                        encrypt += matrix[r1][(c1 + 1) % 5];
                        encrypt += matrix[r2][(c2 + 1) % 5];
                    } else if (c1 == c2) { // Same Col
                        encrypt += matrix[(r1 + 1) % 5][c1];
                        encrypt += matrix[(r2 + 1) % 5][c2];
                    } else { // Rectangle
                        encrypt += matrix[r1][c2];
                        encrypt += matrix[r2][c1];
                    }
                }
            }
            if (i != text.length() - 1) encrypt += '#';
            word = ""; 
        } else {
            char ch = toupper(text[i]);
            if (ch == 'J') ch = 'I';
            word += ch;
        }
    }
    return encrypt;
}

string decryptText(string encrypt, char matrix[5][5], string decrypt) {
    string word = "";
    encrypt += "#"; 

    for (int i = 0; i < encrypt.length(); i++) {
        if (encrypt[i] == '#') {
            if (word.length() > 0) {
                for(int j = 0; j < word.length(); j += 2) {
                    int r1, c1, r2, c2;
                    findPos(matrix, word[j], r1, c1);
                    findPos(matrix, word[j+1], r2, c2);

                    if (r1 == r2) { // Same Row (Shift Left)
                        decrypt += tolower(matrix[r1][(c1 - 1 + 5) % 5]);
                        decrypt += tolower(matrix[r2][(c2 - 1 + 5) % 5]);
                    } else if (c1 == c2) { // Same Col (Shift Up)
                        decrypt += tolower(matrix[(r1 - 1 + 5) % 5][c1]);
                        decrypt += tolower(matrix[(r2 - 1 + 5) % 5][c2]);
                    } else { // Rectangle
                        decrypt += tolower(matrix[r1][c2]);
                        decrypt += tolower(matrix[r2][c1]);
                    }
                }
            }
            if (i != encrypt.length() - 1) decrypt += ' ';
            word = "";
        } else {
            word += toupper(encrypt[i]);
        }
    }
    // remove X from the decrypted text if they were added during encryption
    string finalDecrypt = "";
    for (int i = 0; i < decrypt.length(); i++) {
        if (decrypt[i] != 'x') {
            finalDecrypt += decrypt[i];
        }
    }
    decrypt = finalDecrypt;
    return decrypt;
}

int main() {
    string text, key, encrypt = "", decrypt = "";

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }
    
    getline(inFile, text);
    inFile >> key; 
    inFile.close();

    // 1. Make a single string of 25 unique characters
    string tempStr = "";
    string fullKey = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    for (int i = 0; i < fullKey.length(); i++) {
        char ch = toupper(fullKey[i]);
        if (ch == 'J') ch = 'I';
        if (tempStr.find(ch) == -1) { 
            tempStr += ch;
        }
    }

    // 2. Drop the string into a 5x5 array (easy noob way)
    char matrix[5][5];
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = tempStr[index];
            index++;
        }
    }

    encrypt = encryptText(text, matrix, encrypt);
    decrypt = decryptText(encrypt, matrix, decrypt);
    
    cout << "Original Text: " << text << endl;
    cout << "Key: " << key << endl;
    
    cout << "--- Matrix ---" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------" << endl;

    cout << "Encrypted Text: " << encrypt << endl;
    cout << "Decrypted Text: " << decrypt << endl;

    return 0;
}