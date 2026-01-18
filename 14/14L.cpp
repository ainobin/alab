/**
 * PROBLEM: 14 - Left Most Derivation
 * 
 * ALGORITHM:
 * 1. Start with the start symbol
 * 2. Find the leftmost non-terminal (uppercase letter)
 * 3. Replace it with one of its productions
 * 4. Repeat until no non-terminals remain or max steps reached
 * 
 * EXAMPLE:
 * Grammar: S -> iEtSeS | a, E -> b
 * Derivation: S => iEtSeS => ibtSeS => ibtaeS => ibtaea
 */

#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
char startSymbol;

int main()
{
    ifstream file("inputL.txt");
    
    if (!file.is_open()) {
        cout << "Error: inputL.txt not found!" << endl;
        return 1;
    }

    int n;
    file >> n;
    file.ignore(); // ignore newline after the number

    // Read all productions for each non-terminal
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(file, line);
        
        if (line.empty()) {
            i--;
            continue;
        }
        
        stringstream ss(line);
        char lhs;
        ss >> lhs;  // Read non-terminal
        
        if (i == 0)
            startSymbol = lhs;
        
        // Read ALL productions on this line
        string rhs;
        while (ss >> rhs) {
            grammar[lhs].push_back(rhs);
        }
    }
    file.close();

    // Show grammar
    cout << "\nGrammar:\n";
    for (auto& entry : grammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            if (i > 0) cout << " | ";
            cout << entry.second[i];
        }
        cout << "\n";
    }
    
    string result;
    result += startSymbol;

    cout << "\nLeftmost Derivation:\n";
    cout << result << endl;
    
    const int MAX_STEPS = 50;  // Prevent infinite loops
    int step = 0;

    while (step < MAX_STEPS)
    {
        bool replaced = false;

        for (int i = 0; i < result.length(); i++)
        {
            if (isupper(result[i])) // check if non-terminal
            {
                char nt = result[i];
                
                // Check if non-terminal exists
                if (grammar.find(nt) == grammar.end()) {
                    cout << "\nError: No production for '" << nt << "'" << endl;
                    return 1;
                }
                
                string prod = grammar[nt][0]; // choose first production

                if (prod == "e")
                    result.replace(i, 1, "");
                else
                    result.replace(i, 1, prod);

                cout << "=> " << result << endl;
                replaced = true;
                step++;
                break;
            }
        }

        if (!replaced)
            break;
    }
    
    if (step >= MAX_STEPS) {
        cout << "\n[Stopped at " << MAX_STEPS << " steps - possible infinite derivation]" << endl;
    } else {
        cout << "\nDerivation complete!" << endl;
    }

    return 0;
}
