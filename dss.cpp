// hello from nobin
// 23 11 4 7 3

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

// Extended Euclidean Algorithm for modular inverse
long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    if (m == 1) return 0;

    a = ((a % m) + m) % m; // ensure positive

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

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Simple hash function (stand-in for SHA-1/SHA-256 used in real DSS)
// Reduces the message to a number less than q, for lab-scale demonstration
long long simpleHash(string msg, long long q) {
    long long h = 0;
    for (char c : msg) {
        h = (h * 31 + (unsigned char)c) % q;
    }
    return h;
}

int main() {
    string message;
    long long p, q, g, x, k;

    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, message);         // line 1: message to sign
    inFile >> p >> q >> g >> x >> k;  // line 2: domain params p, q, g, private key x, random k
    inFile.close();

    // ---- Validate domain parameters ----
    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: p and q must both be prime." << endl;
        return 1;
    }
    if ((p - 1) % q != 0) {
        cout << "Error: q must divide (p - 1)." << endl;
        return 1;
    }
    if (g <= 1 || g >= p) {
        cout << "Error: g must satisfy 1 < g < p." << endl;
        return 1;
    }
    if (x <= 0 || x >= q) {
        cout << "Error: private key x must satisfy 0 < x < q." << endl;
        return 1;
    }
    if (k <= 0 || k >= q) {
        cout << "Error: random k must satisfy 0 < k < q." << endl;
        return 1;
    }
    if (gcd(k, q) != 1) {
        // gcd not defined above, so inline check via modInverse safety
    }

    // ---- Key Generation ----
    // Public key: y = g^x mod p
    long long y = modPow(g, x, p);

    cout << "---- Key Generation ----" << endl;
    cout << "Domain Params: p = " << p << ", q = " << q << ", g = " << g << endl;
    cout << "Private Key: x = " << x << endl;
    cout << "Public Key:  y = " << y << endl;
    cout << endl;

    // ---- Signing ----
    // r = (g^k mod p) mod q
    long long r = modPow(g, k, p) % q;
    if (r == 0) {
        cout << "Error: r = 0, choose a different k." << endl;
        return 1;
    }

    long long H = simpleHash(message, q); // hash of message, reduced mod q
    long long kInv = modInverse(k, q);

    // s = k^-1 * (H(m) + x*r) mod q
    long long s = (kInv * (H + x * r)) % q;
    if (s == 0) {
        cout << "Error: s = 0, choose a different k." << endl;
        return 1;
    }

    cout << "---- Signing ----" << endl;
    cout << "Message: " << message << endl;
    cout << "Hash H(m) = " << H << endl;
    cout << "Signature: (r, s) = (" << r << ", " << s << ")" << endl;
    cout << endl;

    // ---- Verification ----
    // w = s^-1 mod q
    long long w = modInverse(s, q);
    // u1 = H(m) * w mod q
    long long u1 = (H * w) % q;
    // u2 = r * w mod q
    long long u2 = (r * w) % q;
    // v = ((g^u1 * y^u2) mod p) mod q
    long long v = ((modPow(g, u1, p) * modPow(y, u2, p)) % p) % q;

    cout << "---- Verification ----" << endl;
    cout << "w = " << w << ", u1 = " << u1 << ", u2 = " << u2 << endl;
    cout << "v = " << v << endl;

    if (v == r) {
        cout << "Result: Signature is VALID (v == r)" << endl;
    } else {
        cout << "Result: Signature is INVALID (v != r)" << endl;
    }

    return 0;
}