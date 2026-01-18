/*
 * 04 Write a C++ program to test whether a given identifier is valid or not.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file;
    string word;
    file.open("input.txt");
    file >> word;

    set<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"};

    bool isValid = true;

    if (keywords.count(word) || !(isalpha(word[0]) || word[0] == '_' || word[0] == '$'))
        isValid = false;
    else
    {
        for (int i = 1; i < word.length(); i++)
        {
            if (!(isalnum(word[i]) || word[i] == '_' || word[i] == '$'))
            {
                isValid = false;
                break;
            }
        }
    }

    if (isValid)
        cout << "This is a valid Identifier" << endl;
    else
        cout << "This is a invalid Identifier" << endl;
}
