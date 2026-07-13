// HI
// 7 11


#include <bits/stdc++.h>
using namespace std;

// Modular exponentiation: (base^exp) % mod
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Extended Euclidean Algorithm: returns gcd, and sets x, y such that a*x + b*y = gcd
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    string text;
    long long p, q;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);   // line 1: plaintext message
    inFile >> p >> q;        // line 2: two primes p, q (both must be ≡ 3 mod 4)
    inFile.close();

    // ---- Validate inputs ----
    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: p and q must both be prime." << endl;
        return 1;
    }
    if (p == q) {
        cout << "Error: p and q must be distinct." << endl;
        return 1;
    }
    if (p % 4 != 3 || q % 4 != 3) {
        cout << "Error: p and q must both be congruent to 3 mod 4 "
             << "(required so square roots mod p, mod q can be computed directly)." << endl;
        return 1;
    }

    long long n = p * q; // public key

    cout << "---- Key Generation ----" << endl;
    cout << "p = " << p << ", q = " << q << endl;
    cout << "Public Key:  n = " << n << endl;
    cout << "Private Key: (p, q) = (" << p << ", " << q << ")" << endl;
    cout << endl;

    // ---- Encryption ----
    // For each character, embed redundancy (repeat the byte) so we can
    // pick the correct root among the 4 candidates during decryption.
    // C = M^2 mod n
    cout << "---- Encryption ----" << endl;
    cout << "Original Text: " << text << endl;

    vector<long long> cipherValues;
    bool overflowWarning = false;
    for (char ch : text) {
        long long b = (long long)(unsigned char)ch;
        long long m = (b << 8) | b; // redundancy: repeat byte -> 16-bit value "bb"
        if (m >= n) overflowWarning = true;
        long long c = (m * m) % n;
        cipherValues.push_back(c);
    }

    if (overflowWarning) {
        cout << "Warning: Some encoded values are >= n. Choose larger primes." << endl;
    }

    cout << "Encrypted Values: ";
    for (long long c : cipherValues) cout << c << " ";
    cout << endl << endl;

    // ---- Decryption ----
    // Compute square roots of C mod p and mod q, then combine via CRT
    // to get 4 candidate roots mod n. Pick the one matching the redundancy pattern.
    cout << "---- Decryption ----" << endl;

    string decryptedText = "";
    for (long long c : cipherValues) {
        // Since p ≡ 3 mod 4, square root mod p is: c^((p+1)/4) mod p
        long long mp = modPow(c % p, (p + 1) / 4, p);
        long long mq = modPow(c % q, (q + 1) / 4, q);

        // CRT setup: find yP, yQ such that yP*p + yQ*q = 1
        long long yP, yQ;
        extGCD(p, q, yP, yQ);

        // Four candidate roots mod n
        long long r1 = ((mp * yQ % n) * q % n + (mq * yP % n) * p % n) % n;
        if (r1 < 0) r1 += n;
        long long r2 = n - r1;
        // second pair uses -mp (or -mq) to get the other two roots
        long long r3 = (((p - mp) * yQ % n) * q % n + (mq * yP % n) * p % n) % n;
        if (r3 < 0) r3 += n;
        long long r4 = n - r3;

        vector<long long> candidates = {r1, r2, r3, r4};

        // Pick the candidate matching redundancy: high byte == low byte
        long long correctM = -1;
        for (long long cand : candidates) {
            long long hi = (cand >> 8) & 0xFF;
            long long lo = cand & 0xFF;
            if (hi == lo) {
                correctM = lo;
                break;
            }
        }

        if (correctM == -1) {
            cout << "Warning: No candidate matched redundancy check for a character; "
                 << "skipping." << endl;
            continue;
        }

        decryptedText += (char)correctM;
    }

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}