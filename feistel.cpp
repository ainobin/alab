// hello world from nobin
// 4
// 101 202 303 404

#include <bits/stdc++.h>
using namespace std;

// Simple round function F(R, K) - XOR based with a bit rotation for diffusion
// In real DES this would be substitution boxes (S-boxes) + permutation;
// here we use a lightweight version suitable for lab demonstration
unsigned int roundFunction(unsigned int R, unsigned int K) {
    unsigned int temp = R ^ K;
    // simple left rotate by 3 bits for extra diffusion (within 16-bit half-block)
    temp = ((temp << 3) | (temp >> (16 - 3))) & 0xFFFF;
    return temp;
}

// Encrypt a single 32-bit block using Feistel structure with 'rounds' rounds
unsigned int feistelEncryptBlock(unsigned int block, vector<unsigned int> &roundKeys, int rounds) {
    unsigned int L = (block >> 16) & 0xFFFF; // left 16 bits
    unsigned int R = block & 0xFFFF;         // right 16 bits

    for (int i = 0; i < rounds; i++) {
        unsigned int newL = R;
        unsigned int newR = L ^ roundFunction(R, roundKeys[i]);
        L = newL;
        R = newR;
    }

    // Note: final round output is NOT swapped (standard Feistel design choice)
    return ((L & 0xFFFF) << 16) | (R & 0xFFFF);
}

// Decrypt: same structure, but round keys applied in REVERSE order
unsigned int feistelDecryptBlock(unsigned int block, vector<unsigned int> &roundKeys, int rounds) {
    unsigned int L = (block >> 16) & 0xFFFF;
    unsigned int R = block & 0xFFFF;

    for (int i = rounds - 1; i >= 0; i--) {
        unsigned int newR = L;
        unsigned int newL = R ^ roundFunction(L, roundKeys[i]);
        L = newL;
        R = newR;
    }

    return ((L & 0xFFFF) << 16) | (R & 0xFFFF);
}

// Convert a 4-character string chunk into a 32-bit block
unsigned int stringToBlock(string s) {
    while (s.length() < 4) s += 'X'; // pad
    unsigned int block = 0;
    for (int i = 0; i < 4; i++) {
        block = (block << 8) | (unsigned char)s[i];
    }
    return block;
}

// Convert a 32-bit block back into a 4-character string
string blockToString(unsigned int block) {
    string s = "";
    for (int i = 3; i >= 0; i--) {
        char c = (block >> (i * 8)) & 0xFF;
        s += c;
    }
    return s;
}

int main() {
    string text;
    int rounds;
    vector<unsigned int> roundKeys;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);
    inFile >> rounds;

    // Read 'rounds' number of round keys (as integers)
    for (int i = 0; i < rounds; i++) {
        unsigned int k;
        inFile >> k;
        roundKeys.push_back(k & 0xFFFF); // keep keys within 16-bit range
    }
    inFile.close();

    // Break text into 4-character blocks, encrypt each block
    vector<unsigned int> encryptedBlocks;
    for (size_t i = 0; i < text.length(); i += 4) {
        string chunk = text.substr(i, 4);
        unsigned int block = stringToBlock(chunk);
        unsigned int enc = feistelEncryptBlock(block, roundKeys, rounds);
        encryptedBlocks.push_back(enc);
    }

    // Decrypt each block back
    string decryptedText = "";
    string encryptedHex = "";
    for (unsigned int enc : encryptedBlocks) {
        stringstream ss;
        ss << hex << uppercase << setfill('0') << setw(8) << enc;
        encryptedHex += ss.str() + " ";

        unsigned int dec = feistelDecryptBlock(enc, roundKeys, rounds);
        decryptedText += blockToString(dec);
    }

    cout << "Original Text: " << text << endl;
    cout << "Rounds: " << rounds << endl;
    cout << "Encrypted Text (hex blocks): " << encryptedHex << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}