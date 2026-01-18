/*
 * 05 Write a C++ program to recognize strings under 'a', 'a*b+', 'abb'.
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file;
    string word;
    file.open("input.txt");
    file >> word;

    cout<< word << endl;
    
    // Check for 'a'
    if (word == "a")
    {
        cout << "String belongs to language: a" << endl;
    }
    // Check for 'abb'
    else if (word == "abb")
    {
        cout << "String belongs to language: abb" << endl;
    }
    // Check for 'a*b+' (zero or more 'a's followed by one or more 'b's)
    else
    {
        int index = 0;
        bool isValid = true;
        
        // Find the first 'b'
        for (int i = 0; i < word.size(); i++)
        {
            if (word[i] == 'b')
            {
                index = i;
                break;
            }
            else if (word[i] != 'a')
            {
                isValid = false;
                break;
            }
        }
        
        // Check if at least one 'b' exists
        if (index == 0 && word[0] != 'b')
        {
            isValid = false;
        }
        
        // Verify all characters after first 'b' are also 'b'
        if (isValid)
        {
            for (int i = index; i < word.size(); i++)
            {
                if (word[i] != 'b')
                {
                    isValid = false;
                    break;
                }
            }
        }
        
        if (isValid && index < word.size())
            cout << "String belongs to language: a*b+" << endl;
        else
            cout << "Did not match any language." << endl;
    }
    
    file.close();
    return 0;
}