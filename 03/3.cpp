/*
 * 03 Write a C++ program to identify whether a given line is a comment or not.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file;
    string line;

    file.open("input.txt");
    getline(file, line);

    cout << line <<endl;

    if (line.size() >= 2 &&
        line[0] == '/' && line[1] == '/')
    {
        cout << "Single-line comment" << endl;
    }
    else if (line.size() >= 4 &&
             line[0] == '/' && line[1] == '*' &&
             line[line.size() - 2] == '*' &&
             line[line.size() - 1] == '/')
    {
        cout << "Multi-line comment" << endl;
    }
    else
    {
        cout << "Not a comment" << endl;
    }

    file.close();
    return 0;
}
