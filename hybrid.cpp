// transpotation

#include <bits/stdc++.h>
using namespace std;

// ---------- STAGE 1: Keyless Transposition (2-row method) ----------
string keylessEncrypt(string text) {
    string clean = "";
    for (char c : text) {
        if (c != ' ') clean += toupper(c);
    }

    if (clean.length() % 2 != 0) clean += 'X'; // pad to even length
    int cols = clean.length() / 2;

    string row1 = clean.substr(0, cols);
    string row2 = clean.substr(cols, cols);

    string result = "";
    for (int i = 0; i < cols; i++) {
        result += row1[i];
        result += row2[i];
    }
    return result;
}

string keylessDecrypt(string text) {
    int cols = text.length() / 2;
    string row1 = "", row2 = "";
    for (int i = 0; i < (int)text.length(); i += 2) {
        row1 += text[i];
        row2 += text[i + 1];
    }
    return row1 + row2;
}

// ---------- STAGE 2: Keyed Columnar Transposition ----------
string keyedEncrypt(string text, string key) {
    int cols = key.length();
    int rows = (text.length() + cols - 1) / cols;

    while (text.length() < (size_t)(rows * cols)) {
        text += 'X';
    }

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < cols; i++) {
        keyOrder.push_back({toupper(key[i]), i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    vector<string> grid(rows);
    int idx = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r] += text[idx++];
        }
    }

    string result = "";
    for (int k = 0; k < cols; k++) {
        int colIndex = keyOrder[k].second;
        for (int r = 0; r < rows; r++) {
            result += grid[r][colIndex];
        }
    }
    return result;
}

string keyedDecrypt(string text, string key) {
    int cols = key.length();
    int rows = text.length() / cols;

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < cols; i++) {
        keyOrder.push_back({toupper(key[i]), i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    vector<string> grid(rows, string(cols, ' '));
    int idx = 0;
    for (int k = 0; k < cols; k++) {
        int colIndex = keyOrder[k].second;
        for (int r = 0; r < rows; r++) {
            grid[r][colIndex] = text[idx++];
        }
    }

    string result = "";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            result += grid[r][c];
        }
    }
    return result;
}

// ---------- HYBRID: Stage 1 (keyless) then Stage 2 (keyed) ----------
string encryptText(string text, string key) {
    string stage1 = keylessEncrypt(text);      // keyless transposition first
    string stage2 = keyedEncrypt(stage1, key); // then keyed columnar transposition
    return stage2;
}

string decryptText(string encrypt, string key) {
    string stage1 = keyedDecrypt(encrypt, key);   // undo keyed transposition first
    string stage2 = keylessDecrypt(stage1);       // then undo keyless transposition

    for (int i = 0; i < (int)stage2.length(); i++) {
        stage2[i] = tolower(stage2[i]);
    }
    return stage2;
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