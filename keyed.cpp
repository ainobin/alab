// transpotation 
#include <bits/stdc++.h>
using namespace std;

// Encrypt: arrange text in a grid with 'key.length()' columns
// then read columns in the order determined by the key 
string encryptText(string text, string key) {
    // Remove spaces
    string clean = "";
    for (char c : text) {
        if (c != ' ') clean += toupper(c);
    }

    int cols = key.length();
    int rows = (clean.length() + cols - 1) / cols; // ceil division

    // Pad with 'X' so the grid is completely filled
    while (clean.length() < (size_t)(rows * cols)) {
        clean += 'X';
    }

    // Determine column reading order based on key's alphabetical order
    // e.g. key = "ZEBRA" -> order tells which column to read 1st, 2nd, ...
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < cols; i++) {
        keyOrder.push_back({toupper(key[i]), i});
    }
    sort(keyOrder.begin(), keyOrder.end()); // sorts by char, keeps original index

    // Build the grid (row-wise fill)
    vector<string> grid(rows);
    int idx = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r] += clean[idx++];
        }
    }

    // Read columns in key order
    string encrypt = "";
    for (int k = 0; k < cols; k++) {
        int colIndex = keyOrder[k].second;
        for (int r = 0; r < rows; r++) {
            encrypt += grid[r][colIndex];
        }
    }
    return encrypt;
}

// Decrypt: rebuild the grid column by column using the key order, then read row-wise
string decryptText(string encrypt, string key) {
    int cols = key.length();
    int rows = encrypt.length() / cols;

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < cols; i++) {
        keyOrder.push_back({toupper(key[i]), i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Fill grid column by column, in the key order
    vector<string> grid(rows, string(cols, ' '));
    int idx = 0;
    for (int k = 0; k < cols; k++) {
        int colIndex = keyOrder[k].second;
        for (int r = 0; r < rows; r++) {
            grid[r][colIndex] = encrypt[idx++];
        }
    }

    // Read row-wise to get plaintext back
    string decrypt = "";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            decrypt += tolower(grid[r][c]);
        }
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