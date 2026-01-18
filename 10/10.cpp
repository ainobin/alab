/**
 * PROBLEM: 10: Design a lexical analyzer for the given language. The lexical analyzer should ignore redundant spaces,tabs, new lines, comments etc.
 */

#include <bits/stdc++.h>
using namespace std;

set<string> keywords = {
    "int", "float", "double", "char",
    "if", "else", "for", "while", "do",
    "return", "void", "main"};

set<string> operators = {
    "+", "-", "*", "/", "%", "=",
    "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "+=", "-=", "*=", "/="};

set<char> separators = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.'};

bool isIdentifier(string word)
{
    if (word.empty())
        return false;

    if (!(isalpha(word[0]) || word[0] == '_'))
        return false;
    for (auto c : word)
    {
        if (!(isalnum(c) || c == '_'))
            return false;
    }
    return true;
}

bool isConstant(string word)
{
    if (word.empty())
        return false;

    for (auto c : word)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main()
{
    ifstream file("input.c");
    string line, code;

    while (getline(file, line))
    {
        code += line + '\n';
    }
    file.close();


    for (int i = 0; i < code.size();)
    {
        // Ignore spaces,tabs,newlines
        if (isspace(code[i]))
        {
            i++;
            continue;
        }

        // ignore single-line comments
        if (code[i] == '/' && (i + 1) < code.size() && code[i + 1] == '/')
        {
            while (i < code.size() && code[i] != '\n')
                i++;
            continue;
        }

        // ignore multi-line
        if (code[i] == '/' && (i + 1) < code.size() && code[i + 1] == '*')
        {
            i += 2;
            while (i + 1 < code.size() && !(code[i] == '*' && code[i + 1] == '/'))
                i++;
            i += 2;
            continue;
        }

        // check two characters operator
        if (i + 1 < code.size())
        {
            string twoChar = code.substr(i, 2);
            if (operators.count(twoChar))
            {
                cout << "Operator: " << twoChar << endl;
                i += 2;
                continue;
            }
        }

        // check one character operator
        string oneChar = code.substr(i, 1);
        if (operators.count(oneChar))
        {
            cout << "Operator: " << oneChar << endl;
            i++;
            continue;
        }

        // separator
        if (separators.count(code[i]))
        {
            cout << "Separator: " << code[i] << endl;
            i++;
            continue;
        }

        // Extract token
        string token = "";
        while (i < code.size() && !isspace(code[i]) && !operators.count(code.substr(i, 1)) && !separators.count(code[i]))
        {
            token += code[i];
            i++;
        }
        if (keywords.count(token))
            cout << "Keyword " << token << endl;
        else if (isConstant(token))
            cout << "Constant " << token << endl;
        else if (isIdentifier(token))
            cout << "Identifier " << token << endl;
        else
            cout << "Invalid token" << endl;
    }
}