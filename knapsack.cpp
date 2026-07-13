// Hi
// superincreasing numbers (private key): 2 3 6 13 27 52 105 210
// modulus (bigger than the sum of the private key): 467 105

#include <bits/stdc++.h>
using namespace std;

// Extended Euclidean Algorithm for modular inverse
long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    if (m == 1) return 0;

    a = ((a % m) + m) % m;

    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;
    return x1;
}

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Check if a sequence is superincreasing (each term > sum of all previous terms)
bool isSuperincreasing(vector<long long> &seq) {
    long long sum = 0;
    for (long long val : seq) {
        if (val <= sum) return false;
        sum += val;
    }
    return true;
}

int main() {
    string text;
    vector<long long> privateKey; // superincreasing sequence
    long long q, r; // modulus and multiplier for generating public key

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text); // line 1: plaintext (only letters, will convert to 8-bit binary per char)

    // line 2: 8 numbers forming the private superincreasing sequence
    privateKey.resize(8);
    for (int i = 0; i < 8; i++) inFile >> privateKey[i];

    inFile >> q >> r; // line 3: modulus q, multiplier r
    inFile.close();

    // ---- Validate ----
    if (!isSuperincreasing(privateKey)) {
        cout << "Error: Private key sequence must be superincreasing "
             << "(each term > sum of all previous terms)." << endl;
        return 1;
    }

    long long sumPrivate = 0;
    for (long long v : privateKey) sumPrivate += v;

    if (q <= sumPrivate) {
        cout << "Error: q must be greater than the sum of all private key terms ("
             << sumPrivate << ")." << endl;
        return 1;
    }
    if (gcd(q, r) != 1) {
        cout << "Error: r must be coprime with q." << endl;
        return 1;
    }
    if (r <= 1 || r >= q) {
        cout << "Error: r must satisfy 1 < r < q." << endl;
        return 1;
    }

    // ---- Key Generation ----
    // Public key: each private term * r mod q (this "disguises" the superincreasing sequence)
    vector<long long> publicKey(8);
    for (int i = 0; i < 8; i++) {
        publicKey[i] = (privateKey[i] * r) % q;
    }

    cout << "---- Key Generation ----" << endl;
    cout << "Private Key (superincreasing): ";
    for (long long v : privateKey) cout << v << " ";
    cout << endl;
    cout << "Modulus q = " << q << ", Multiplier r = " << r << endl;
    cout << "Public Key (disguised, sent openly): ";
    for (long long v : publicKey) cout << v << " ";
    cout << endl << endl;

    // ---- Encryption ----
    // Each character's 8-bit binary representation selects which public key
    // terms to sum -> that sum is the ciphertext value for that character.
    cout << "---- Encryption ----" << endl;
    cout << "Original Text: " << text << endl;

    vector<long long> cipherValues;
    for (char ch : text) {
        unsigned char b = (unsigned char)ch;
        long long sum = 0;
        for (int bit = 7; bit >= 0; bit--) {
            if ((b >> bit) & 1) {
                sum += publicKey[7 - bit];
            }
        }
        cipherValues.push_back(sum);
    }

    cout << "Encrypted Values: ";
    for (long long c : cipherValues) cout << c << " ";
    cout << endl << endl;

    // ---- Decryption ----
    // Step 1: compute r^-1 mod q
    // Step 2: c' = C * r^-1 mod q  -> this maps back to the superincreasing knapsack problem
    // Step 3: solve superincreasing knapsack greedily (easy, unlike general knapsack)
    cout << "---- Decryption ----" << endl;

    long long rInv = modInverse(r, q);
    string decryptedText = "";

    for (long long c : cipherValues) {
        long long cPrime = (c * rInv) % q;

        // Solve superincreasing knapsack: work from largest term down
        unsigned char byteVal = 0;
        long long remainder = cPrime;
        for (int i = 7; i >= 0; i--) {
            if (privateKey[i] <= remainder) {
                byteVal |= (1 << (7 - i));
                remainder -= privateKey[i];
            }
        }
        decryptedText += (char)byteVal;
    }

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}