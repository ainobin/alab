/**
 * PROBLEM: 09: Write a cpp program to implement DFA that recognized identifiers, constant and operators
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input.txt");
    string word;
    file >> word;
    file.close();

    // Check for Identifier
    if (isalpha(word[0]) || word[0] == '_' || word[0] == '$')
    {
        bool isIdentifier = true;
        for (int i = 1; i < word.size(); i++)
        {
            if (!isalnum(word[i]) && word[i] != '_')
            {
                isIdentifier = false;
                break;
            }
        }
        if (isIdentifier)
        {
            cout << "Identifier" << endl;
            return 0;
        }
    }

    // Check for Constant (all digits)
    if (isdigit(word[0]))
    {
        bool isConstant = true;
        for (int i = 1; i < word.size(); i++)
        {
            if (!isdigit(word[i]))
            {
                isConstant = false;
                break;
            }
        }
        if (isConstant)
        {
            cout << "Constant" << endl;
            return 0;
        }
    }

    // Check for Operators
    if (word == "+" || word == "-" || word == "*" || word == "/" || 
        word == "=" || word == "<" || word == ">" ||
        word == "++" || word == "--" || word == "+=" || word == "-=" ||
        word == "*=" || word == "/=" || word == "==" || word == "<=" || word == ">=")
    {
        cout << "Operator" << endl;
        return 0;
    }

    cout << "Invalid" << endl;
    return 0;
}