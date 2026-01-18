/*
 * 07 Write a C++ program to count the number of operators from a given string.
 */

#include <bits/stdc++.h>
using namespace std;

set<string> operators = {
    "+", "-", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=",
    "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "++", "--"};

bool isOperator(string word)
{
    return operators.count(word);
}

int main()
{
    ifstream file;
    string line;
    int operatorCount = 0;

    file.open("input.txt");
    getline(file, line);

    for (int i = 0; i < line.size(); i++)
    {
        if ((i + 1) < line.size())
        {
            string twoChar = line.substr(i, 2);
            if (isOperator(twoChar))
            {
                operatorCount++;
                i++;
                continue;
            }
        }

        string oneChar = line.substr(i, 1);
        if (isOperator(oneChar))
            operatorCount++;
    }
    cout << "Total operators are " << operatorCount << endl;
}
