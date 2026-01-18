/*
 * PROBLEM: 08 Write a C++ program to implement NFA that recognize identifiers
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input.txt");
    string identifier;
    file >> identifier;
    file.close();

    bool isValid = false;

    // First character must be letter or underscore
    if (isalpha(identifier[0]) || identifier[0] == '_' || identifier[0] == '$')
    {
        isValid = true;
        // Remaining characters must be letter, digit, or underscore
        for (int i = 1; i < identifier.size(); i++)
        {
            if (!isalnum(identifier[i]) && identifier[i] != '_' && identifier[i] != '$')
            {
                isValid = false;
                break;
            }
        }
    }

    if (isValid)
        cout << identifier << " is valid" << endl;
    else
        cout << identifier << " is not valid" << endl;

    return 0;
}