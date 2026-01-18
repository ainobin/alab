/**
 * PROBLEM: 12: Write a C++ program to find FOLLOW values from a given set of productions
 * 
 * FOLLOW SET RULES:
 * 1. FOLLOW(Start Symbol) contains $
 * 2. If A -> αBβ, then FIRST(β) - {ε} is in FOLLOW(B)
 * 3. If A -> αB or A -> αBβ where ε ∈ FIRST(β), then FOLLOW(A) is in FOLLOW(B)
 */

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;      // Grammar rules
map<string, set<string>> firstSets;       // FIRST sets for all symbols
map<string, set<string>> followSets;      // FOLLOW sets for non-terminals
string startSymbol;                        // Start symbol of grammar

// Check if a symbol is terminal (lowercase or special character)
bool isTerminal(string symbol) {
    return !isupper(symbol[0]);
}

// Parse a string into individual symbols
// Example: "TE'" becomes ["T", "E'"]
vector<string> parseSymbols(string str) {
    vector<string> symbols;
    int i = 0;
    
    while (i < str.length()) {
        string currentSymbol = "";
        
        // Check for two-character symbols
        if (i + 1 < str.length()) {
            string twoChar = str.substr(i, 2);
            
            if (twoChar == "id") {
                currentSymbol = "id";
                i += 2;
            }
            else if (twoChar[1] == '\'') {  // Like "E'" or "T'"
                currentSymbol = twoChar;
                i += 2;
            }
        }
        
        // Single character symbol
        if (currentSymbol == "") {
            currentSymbol = string(1, str[i]);
            i++;
        }
        
        symbols.push_back(currentSymbol);
    }
    
    return symbols;
}

// Compute FIRST set for a non-terminal
void computeFirst(string nonTerminal) {
    // Already computed
    if (!firstSets[nonTerminal].empty()) {
        return;
    }
    
    // Process each production of this non-terminal
    for (string production : grammar[nonTerminal]) {
        vector<string> symbols = parseSymbols(production);
        bool allHaveEpsilon = true;
        
        for (string symbol : symbols) {
            // Terminal: add it and stop
            if (isTerminal(symbol)) {
                firstSets[nonTerminal].insert(symbol);
                allHaveEpsilon = false;
                break;
            }
            // Non-terminal: compute its FIRST recursively
            else {
                computeFirst(symbol);
                
                // Add FIRST(symbol) except epsilon
                bool hasEpsilon = false;
                for (string f : firstSets[symbol]) {
                    if (f == "e") {
                        hasEpsilon = true;
                    } else {
                        firstSets[nonTerminal].insert(f);
                    }
                }
                
                // If no epsilon, stop here
                if (!hasEpsilon) {
                    allHaveEpsilon = false;
                    break;
                }
            }
        }
        
        // All symbols can derive epsilon
        if (allHaveEpsilon) {
            firstSets[nonTerminal].insert("e");
        }
    }
}

// Get FIRST of a sequence of symbols
// Example: FIRST("TE'") or FIRST("+TE'")
set<string> getFirstOfSequence(vector<string> symbols) {
    set<string> result;
    
    for (string symbol : symbols) {
        // Terminal: add it and done
        if (isTerminal(symbol)) {
            result.insert(symbol);
            return result;
        }
        
        // Non-terminal: add FIRST(symbol) except epsilon
        bool hasEpsilon = false;
        for (string f : firstSets[symbol]) {
            if (f == "e") {
                hasEpsilon = true;
            } else {
                result.insert(f);
            }
        }
        
        // If no epsilon, done
        if (!hasEpsilon) {
            return result;
        }
    }
    
    // All symbols derive epsilon
    result.insert("e");
    return result;
}

// Compute FOLLOW set for a non-terminal
void computeFollow() {
    // Rule 1: Add $ to start symbol
    followSets[startSymbol].insert("$");
    
    // Iterate multiple times to handle dependencies
    bool changed = true;
    int iterations = 0;
    
    while (changed && iterations < 10) {
        changed = false;
        iterations++;
        
        // Check every production in grammar
        for (auto& entry : grammar) {
            string leftSide = entry.first;  // Left-hand side (A)
            
            for (string production : entry.second) {
                vector<string> symbols = parseSymbols(production);
                
                // Look at each symbol in the right-hand side
                for (int i = 0; i < symbols.size(); i++) {
                    string currentSymbol = symbols[i];
                    
                    // Only compute FOLLOW for non-terminals
                    if (isTerminal(currentSymbol)) {
                        continue;
                    }
                    
                    // Get symbols after current symbol (β)
                    vector<string> beta;
                    for (int j = i + 1; j < symbols.size(); j++) {
                        beta.push_back(symbols[j]);
                    }
                    
                    // Rule 2: If A -> αBβ, add FIRST(β) - {ε} to FOLLOW(B)
                    if (!beta.empty()) {
                        set<string> firstOfBeta = getFirstOfSequence(beta);
                        
                        bool hasEpsilon = false;
                        for (string f : firstOfBeta) {
                            if (f == "e") {
                                hasEpsilon = true;
                            } else {
                                if (followSets[currentSymbol].find(f) == followSets[currentSymbol].end()) {
                                    followSets[currentSymbol].insert(f);
                                    changed = true;
                                }
                            }
                        }
                        
                        // Rule 3: If ε ∈ FIRST(β), add FOLLOW(A) to FOLLOW(B)
                        if (hasEpsilon) {
                            for (string f : followSets[leftSide]) {
                                if (followSets[currentSymbol].find(f) == followSets[currentSymbol].end()) {
                                    followSets[currentSymbol].insert(f);
                                    changed = true;
                                }
                            }
                        }
                    }
                    // Rule 3: If A -> αB (nothing after B), add FOLLOW(A) to FOLLOW(B)
                    else {
                        for (string f : followSets[leftSide]) {
                            if (followSets[currentSymbol].find(f) == followSets[currentSymbol].end()) {
                                followSets[currentSymbol].insert(f);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Read input file
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }
    
    int numProductions;
    inputFile >> numProductions;
    inputFile.ignore();
    
    // Read all productions
    bool firstProduction = true;
    for (int i = 0; i < numProductions; i++) {
        string line;
        getline(inputFile, line);
        
        stringstream ss(line);
        string lhs, rhs;
        ss >> lhs >> rhs;
        
        // First production's LHS is the start symbol
        if (firstProduction) {
            startSymbol = lhs;
            firstProduction = false;
        }
        
        grammar[lhs].push_back(rhs);
    }
    inputFile.close();
    
    // Step 1: Compute FIRST sets (needed for FOLLOW computation)
    cout << "Computing FIRST sets...\n";
    for (auto& entry : grammar) {
        computeFirst(entry.first);
    }
    
    // Display FIRST sets
    cout << "\nFIRST Sets:\n";
    cout << "===========\n";
    for (auto& entry : firstSets) {
        cout << "FIRST(" << entry.first << ") = { ";
        bool first = true;
        for (string symbol : entry.second) {
            if (!first) cout << ", ";
            cout << (symbol == "e" ? "ε" : symbol);
            first = false;
        }
        cout << " }\n";
    }
    
    // Step 2: Compute FOLLOW sets
    cout << "\nComputing FOLLOW sets...\n";
    computeFollow();
    
    // Display FOLLOW sets
    cout << "\nFOLLOW Sets:\n";
    cout << "============\n";
    for (auto& entry : grammar) {
        cout << "FOLLOW(" << entry.first << ") = { ";
        bool first = true;
        for (string symbol : followSets[entry.first]) {
            if (!first) cout << ", ";
            cout << symbol;
            first = false;
        }
        cout << " }\n";
    }
    
    return 0;
}