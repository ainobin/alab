/*
Write a C program to scan and count the number of characters, words, and lines in a file.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("2.txt");
    char ch, prev = ' ';
    int characters = 0, words = 0, lines = 1;

    if (!file)
    {
        cout << "File not found!" << endl;
        return 0;
    }

    while (file.get(ch))
    {
        characters++;

        if (ch == '\n')
            lines++;

        if ((ch != ' ' && ch != '\n' && ch != '\t') && (prev == ' ' || prev == '\n' || prev == '\t'))
            words++;

        prev = ch;
    }

    file.close();

    cout << "Characters: " << characters << endl;
    cout << "Words: " << words << endl;
    cout << "Lines: " << lines << endl;

    return 0;
}
