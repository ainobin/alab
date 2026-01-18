/**
 * PROBLEM: 15 - Left Factoring
 * 
 * ALGORITHM:
 * Left factoring removes common prefixes from productions
 * If A -> αβ1 | αβ2 | ...
 * Transform to: A -> αA', A' -> β1 | β2 | ...
 * 
 * EXAMPLE:
 * Input:  S -> iEtS | iEteS | a
 * Output: S -> iEtS' | a, S' -> S | eS
 */

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;
map<string, vector<string>> factoredGrammar;

// Find the longest common prefix between two strings
string findCommonPrefix(string s1, string s2) {
    string prefix = "";
    int minLen = min(s1.length(), s2.length());
    
    for (int i = 0; i < minLen; i++) {
        if (s1[i] == s2[i]) {
            prefix += s1[i];
        } else {
            break;
        }
    }
    
    return prefix;
}

// Perform left factoring for a non-terminal
void performLeftFactoring(string nonTerminal) {
    vector<string> productions = grammar[nonTerminal];
    
    // If only one production or no productions, no factoring needed
    if (productions.size() <= 1) {
        factoredGrammar[nonTerminal] = productions;
        return;
    }
    
    // Group productions by common prefix
    map<string, vector<string>> groups;
    set<int> processed;
    
    for (int i = 0; i < productions.size(); i++) {
        if (processed.find(i) != processed.end()) continue;
        
        string currentProd = productions[i];
        vector<string> group;
        group.push_back(currentProd);
        string commonPrefix = currentProd;
        
        // Find all productions with common prefix
        for (int j = i + 1; j < productions.size(); j++) {
            if (processed.find(j) != processed.end()) continue;
            
            string prefix = findCommonPrefix(currentProd, productions[j]);
            
            if (!prefix.empty()) {
                group.push_back(productions[j]);
                processed.insert(j);
                
                // Update common prefix for the group
                commonPrefix = findCommonPrefix(commonPrefix, productions[j]);
            }
        }
        
        processed.insert(i);
        
        // If group has more than one production with common prefix, factor it
        if (group.size() > 1 && !commonPrefix.empty()) {
            groups[commonPrefix] = group;
        } else {
            // No common prefix, add as is
            factoredGrammar[nonTerminal].push_back(currentProd);
        }
    }
    
    // Create new productions for factored groups
    int primeCount = 0;
    for (auto& entry : groups) {
        string prefix = entry.first;
        vector<string> prods = entry.second;
        
        // Create new non-terminal (e.g., S')
        string newNonTerminal = nonTerminal + "'";
        if (primeCount > 0) {
            newNonTerminal += to_string(primeCount);
        }
        primeCount++;
        
        // Add factored production: A -> αA'
        factoredGrammar[nonTerminal].push_back(prefix + newNonTerminal);
        
        // Add new productions: A' -> β1 | β2 | ...
        for (string prod : prods) {
            string suffix = prod.substr(prefix.length());
            if (suffix.empty()) {
                suffix = "e";  // epsilon
            }
            factoredGrammar[newNonTerminal].push_back(suffix);
        }
    }
}

int main() {
    // Read input
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }
    
    int numNonTerminals;
    inputFile >> numNonTerminals;
    inputFile.ignore();
    
    // Read grammar
    // Format: "S iEtS iEteS a" means S -> iEtS | iEteS | a
    for (int i = 0; i < numNonTerminals; i++) {
        string line;
        getline(inputFile, line);
        
        if (line.empty()) {
            i--;
            continue;
        }
        
        stringstream ss(line);
        string nonTerminal;
        ss >> nonTerminal;
        
        string production;
        while (ss >> production) {
            grammar[nonTerminal].push_back(production);
        }
    }
    inputFile.close();
    
    // Display original grammar
    cout << "Original Grammar:\n";
    cout << "=================\n";
    for (auto& entry : grammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            if (i > 0) cout << " | ";
            cout << entry.second[i];
        }
        cout << "\n";
    }
    
    // Perform left factoring
    cout << "\nPerforming Left Factoring...\n\n";
    for (auto& entry : grammar) {
        performLeftFactoring(entry.first);
    }
    
    // Display factored grammar
    cout << "After Left Factoring:\n";
    cout << "=====================\n";
    for (auto& entry : factoredGrammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            if (i > 0) cout << " | ";
            if (entry.second[i] == "e") {
                cout << "ε";
            } else {
                cout << entry.second[i];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
