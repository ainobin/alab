#include <bits/stdc++.h>
using namespace std;

string encryptText(string text, int key, string encrypt, vector<char> alp)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            encrypt += '#'; // Use '#' to represent space
        }
        else
        {
            char a = toupper(text[i]);
            int ind = a - 65;

            // Apply the multiplicative cipher formula
            int ind_new = (ind * key) % 26;
            encrypt += alp[ind_new];
        }
    }
    return encrypt;
}

string decryptText(string encrypt, int key, string decrypt, vector<char> alp)
{

    // Find the modular multiplicative inverse of the key
    int inverse = 0;
    for (int j = 1; j < 26; j++)
    {
        if ((key * j) % 26 == 1)
        {
            inverse = j;
            break;
        }
    }

    for (int i = 0; i < encrypt.length(); i++)
    {
        if (encrypt[i] == '#')
        {
            decrypt += ' '; // Convert '#' back to space
        }
        else
        {
            char a = encrypt[i];
            int ind = a - 65;

            // Apply the reverse multiplicative cipher formula using the inverse
            int ind_new = (ind * inverse) % 26;

            // Append the decrypted character as lowercase
            decrypt += tolower(alp[ind_new]);
        }
    }
    return decrypt;
}

int main()
{
    vector<char> alp;
    for (int i = 0; i < 26; i++)
    {
        alp.push_back((char)(i + 65));
    }

    string text;
    int key;
    string encrypt = "";
    string decrypt = "";

    // Open the input file
    ifstream inFile("input.txt");
    if (!inFile.is_open())
    {
        cout << "Error: Could not open input.txt." << endl;
        return 1;
    }

    getline(inFile, text);
    inFile >> key;
    inFile.close();

    key = key % 26;
    if (__gcd(key, 26) != 1)
    {
        cout << "Error: key must be coprime with 26 (invalid key: " << key << ")" << endl;
        return 1;
    }

    encrypt = encryptText(text, key, encrypt, alp);
    decrypt = decryptText(encrypt, key, decrypt, alp);

    cout << "Original Text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted Text: " << encrypt << endl;
    cout << "Decrypted Text: " << decrypt << endl;

    return 0;
}