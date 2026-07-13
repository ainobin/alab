#include <bits/stdc++.h>
using namespace std;

// Function to find modular inverse of a number under mod 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // no inverse exists
}

// Encrypt using 2x2 key matrix
string encryptText(string text, int key[2][2]) {
    string encrypt = "";

    // Remove spaces and pad text to even length with 'X'
    string clean = "";
    for (char c : text) {
        if (c != ' ') clean += toupper(c);
    }
    if (clean.length() % 2 != 0) clean += 'X';

    for (int i = 0; i < clean.length(); i += 2) {
        int p1 = clean[i] - 'A';
        int p2 = clean[i + 1] - 'A';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        encrypt += (char)(c1 + 'A');
        encrypt += (char)(c2 + 'A');
    }
    return encrypt;
}

// Decrypt using inverse of the 2x2 key matrix
string decryptText(string encrypt, int key[2][2]) {
    string decrypt = "";

    // Step 1: find determinant
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    det = (det + 26) % 26; // make positive

    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        cout << "Error: Key matrix is not invertible under mod 26." << endl;
        return "";
    }

    // Step 2: find adjugate and multiply by det inverse to get inverse key matrix
    int invKey[2][2];
    invKey[0][0] = (key[1][1] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv) % 26;
    invKey[1][0] = (-key[1][0] * detInv) % 26;
    invKey[1][1] = (key[0][0] * detInv) % 26;

    // make sure all values are positive mod 26
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            invKey[i][j] = ((invKey[i][j] % 26) + 26) % 26;

    for (int i = 0; i < encrypt.length(); i += 2) {
        int c1 = encrypt[i] - 'A';
        int c2 = encrypt[i + 1] - 'A';

        int p1 = (invKey[0][0] * c1 + invKey[0][1] * c2) % 26;
        int p2 = (invKey[1][0] * c1 + invKey[1][1] * c2) % 26;

        decrypt += (char)(tolower(p1 + 'A'));
        decrypt += (char)(tolower(p2 + 'A'));
    }
    return decrypt;
}

int main() {
    string text;
    int key[2][2];

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);
    inFile >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];
    inFile.close();

    string encrypted = encryptText(text, key);
    if (encrypted.empty()) return 1;

    string decrypted = decryptText(encrypted, key);

    cout << "Original Text: " << text << endl;
    cout << "Key Matrix: [" << key[0][0] << " " << key[0][1] << "; "
         << key[1][0] << " " << key[1][1] << "]" << endl;
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}