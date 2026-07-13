// transpotation

#include <bits/stdc++.h>
using namespace std;

// Encrypt: write plaintext in 2 rows, read column by column
string encryptText(string text) {
    // Remove spaces
    string clean = "";
    for (char c : text) {
        if (c != ' ') clean += toupper(c);
    }

    int n = clean.length();
    int cols = (n + 1) / 2; // number of columns needed for 2 rows

    // Pad with 'X' if odd length so both rows are equal
    if (n % 2 != 0) clean += 'X';
    n = clean.length();
    cols = n / 2;

    // Fill 2 rows, row-wise
    string row1 = clean.substr(0, cols);
    string row2 = clean.substr(cols, cols);

    // Read column by column: take one char from row1, one from row2, alternating
    string encrypt = "";
    for (int i = 0; i < cols; i++) {
        encrypt += row1[i];
        encrypt += row2[i];
    }
    return encrypt;
}

// Decrypt: reverse the column-wise reading back into 2 rows, then read row-wise
string decryptText(string encrypt) {
    int n = encrypt.length();
    int cols = n / 2;

    string row1 = "", row2 = "";
    // Undo the column-by-column interleaving
    for (int i = 0; i < n; i += 2) {
        row1 += encrypt[i];
        row2 += encrypt[i + 1];
    }

    string decrypt = row1 + row2;

    // Convert to lowercase for final output
    for (int i = 0; i < decrypt.length(); i++) {
        decrypt[i] = tolower(decrypt[i]);
    }
    return decrypt;
}

int main() {
    string text;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);
    inFile.close();

    string encrypted = encryptText(text);
    string decrypted = decryptText(encrypted);

    cout << "Original Text: " << text << endl;
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}