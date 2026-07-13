// HI
// 61 53 17

#include <bits/stdc++.h>
using namespace std;

// Compute (base^exp) % mod efficiently using modular exponentiation
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

// Compute GCD (used to verify e is coprime with phi(n))
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Compute modular inverse of e mod phi(n) using Extended Euclidean Algorithm
long long modInverse(long long e, long long phi) {
    long long a = e, m = phi;
    long long x0 = 0, x1 = 1;

    if (phi == 1) return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += phi;
    return x1;
}

// Simple primality check (fine for small textbook-scale primes)
bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    long long p, q, e;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    string text;
    getline(inFile, text);      // line 1: plaintext message
    inFile >> p >> q >> e;      // line 2: two primes p, q, and public exponent e
    inFile.close();

    // ---- Validate inputs ----
    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: p and q must both be prime numbers." << endl;
        return 1;
    }
    if (p == q) {
        cout << "Error: p and q must be distinct primes." << endl;
        return 1;
    }

    // ---- Key Generation ----
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    if (gcd(e, phi) != 1) {
        cout << "Error: e must be coprime with phi(n) = " << phi << endl;
        return 1;
    }

    long long d = modInverse(e, phi); // private exponent

    cout << "---- Key Generation ----" << endl;
    cout << "p = " << p << ", q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "phi(n) = " << phi << endl;
    cout << "Public Key  (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n) = (" << d << ", " << n << ")" << endl;
    cout << endl;

    // ---- Encryption ----
    // Each character is converted to its ASCII value, then encrypted individually.
    // Note: ASCII value must be less than n for correct encryption/decryption.
    vector<long long> cipherValues;
    cout << "---- Encryption ----" << endl;
    cout << "Original Text: " << text << endl;

    bool overflowWarning = false;
    for (char c : text) {
        long long m = (long long)(unsigned char)c;
        if (m >= n) overflowWarning = true;
        long long cVal = modPow(m, e, n);
        cipherValues.push_back(cVal);
    }

    if (overflowWarning) {
        cout << "Warning: Some character codes are >= n. Choose larger primes for correct results." << endl;
    }

    cout << "Encrypted Values: ";
    for (long long c : cipherValues) cout << c << " ";
    cout << endl << endl;

    // ---- Decryption ----
    cout << "---- Decryption ----" << endl;
    string decryptedText = "";
    for (long long c : cipherValues) {
        long long m = modPow(c, d, n);
        decryptedText += (char)m;
    }
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}