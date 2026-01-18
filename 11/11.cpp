/**
 * PROBLEM: 11: Write a C++ program to find FIRST values from a given set of productions
 * 
 * ALGORITHM:
 * 1. If X is a terminal, FIRST(X) = {X}
 * 2. If X -> ε, add ε to FIRST(X)
 * 3. If X -> Y1 Y2 ... Yk:
 *    - Add FIRST(Y1) - {ε} to FIRST(X)
 *    - If Y1 can derive ε, add FIRST(Y2) - {ε}, and so on
 *    - If all Yi can derive ε, add ε to FIRST(X)
 */

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;  // Stores productions for each non-terminal
map<string, set<string>> firstSets;   // Stores FIRST set for each symbol

// Check if a symbol is terminal (starts with lowercase or special character)
bool isTerminal(string symbol) {
    return !isupper(symbol[0]);
}

vector<string> parseProduction(string production) {
    vector<string> symbols;
    int i = 0;
    
    while (i < production.length()) {
        string currentSymbol = "";
        
        // Check for two-character symbol: "id" or "E'" or "T'"
        if (i + 1 < production.length()) {
            string twoChar = production.substr(i, 2);
            
            // Is it "id"?
            if (twoChar == "id") {
                currentSymbol = "id";
                i += 2;
            }
            // Is it a prime symbol like "E'" or "T'"?
            else if (twoChar[1] == '\'') {
                currentSymbol = twoChar;
                i += 2;
            }
        }
        
        // If no two-character match, take single character
        if (currentSymbol == "") {
            currentSymbol = string(1, production[i]);
            i++;
        }
        
        symbols.push_back(currentSymbol);
    }
    
    return symbols;
}

// Compute FIRST set for a given non-terminal
void computeFirst(string nonTerminal) {
    // If already computed, return
    if (!firstSets[nonTerminal].empty()) {
        return;
    }
    
    // Process each production rule for this non-terminal
    for (string production : grammar[nonTerminal]) {
        vector<string> symbols = parseProduction(production);
        
        // Check if all symbols can derive epsilon
        bool allDeriveEpsilon = true;
        
        // Process each symbol in the production
        for (string symbol : symbols) {
            // Case 1: Symbol is a terminal
            if (isTerminal(symbol)) {
                firstSets[nonTerminal].insert(symbol);
                allDeriveEpsilon = false;
                break;  // Stop processing this production
            }
            // Case 2: Symbol is a non-terminal
            else {
                // Recursively compute FIRST for this non-terminal
                computeFirst(symbol);
                
                // Add all symbols from FIRST(symbol) except epsilon
                bool symbolHasEpsilon = false;
                for (string firstSymbol : firstSets[symbol]) {
                    if (firstSymbol == "e") {
                        symbolHasEpsilon = true;
                    } else {
                        firstSets[nonTerminal].insert(firstSymbol);
                    }
                }
                
                // If this symbol cannot derive epsilon, stop here
                if (!symbolHasEpsilon) {
                    allDeriveEpsilon = false;
                    break;
                }
            }
        }
        
        // If all symbols can derive epsilon (or production is empty), add epsilon
        if (allDeriveEpsilon) {
            firstSets[nonTerminal].insert("e");
        }
    }
}

int main() {
    // Read input file
    ifstream inputFile("input.txt");
    
    int numProductions;
    inputFile >> numProductions;
    inputFile.ignore();  // Ignore newline after number
    
    // Read all productions
    for (int i = 0; i < numProductions; i++) {
        string line;
        getline(inputFile, line);
        
        // Parse: "E TE'" into lhs="E" and rhs="TE'"
        stringstream ss(line);
        string lhs, rhs;
        ss >> lhs >> rhs;
        
        grammar[lhs].push_back(rhs);
    }
    inputFile.close();
    
    // Compute FIRST set for each non-terminal
    for (auto& entry : grammar) {
        computeFirst(entry.first);
    }
    
    // Display results
    cout << "FIRST Sets:\n";
    cout << "===========\n";
    for (auto& entry : firstSets) {
        cout << "FIRST(" << entry.first << ") = { ";
        
        bool first = true;
        for (string symbol : entry.second) {
            if (!first) cout << ", ";
            // Display epsilon as ε for better readability
            if (symbol == "e") {
                cout << "ε";
            } else {
                cout << symbol;
            }
            first = false;
        }
        
        cout << " }\n";
    }
    
    return 0;
}