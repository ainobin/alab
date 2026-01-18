/*
 * 06 Write a C++ program to simulate lexical analyzer for validating operators.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file;
    string word;
    file.open("input.txt");
    
    set<string> operators = {
        "+", "-", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=",
        "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "++", "--"};
    while (file >> word)
    {
        if (operators.count(word))
            cout << word << " is a valid operator" << endl;
        else
            cout << word << " is not a valid operator" << endl;
    }
}
