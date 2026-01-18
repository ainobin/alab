/**
 * PROBLEM: 13 - Eliminate Left Recursion from a Grammar
 * 
 * ALGORITHM:
 * If we have: A -> Aα | β
 * Transform to: A -> βA' and A' -> αA' | ε
 * 
 * EXAMPLE:
 * Input:  E -> E+T | T
 * Output: E -> TE' and E' -> +TE' | ε
 * 
 * INPUT FORMAT:
 * 2
 * E E+T T
 * T T*F F
 * 
 * This means:
 * E -> E+T | T
 * T -> T*F | F
 */

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;      // Original grammar
map<string, vector<string>> newGrammar;   // After removing left recursion

// Check if a production starts with the non-terminal itself (left recursive)
bool isLeftRecursive(string production, string nonTerminal) {
    // Check if production starts with the non-terminal
    if (production.length() >= nonTerminal.length()) {
        return production.substr(0, nonTerminal.length()) == nonTerminal;
    }
    return false;
}

// Remove left recursion from a single non-terminal
void removeLeftRecursion(string nonTerminal) {
    vector<string> leftRecursive;   // Productions like A -> Aα
    vector<string> notRecursive;    // Productions like A -> β
    
    // Step 1: Separate productions into two groups
    for (string production : grammar[nonTerminal]) {
        if (isLeftRecursive(production, nonTerminal)) {
            // Left recursive: A -> Aα, extract α (part after A)
            string alpha = production.substr(nonTerminal.length());
            leftRecursive.push_back(alpha);
        } else {
            // Not left recursive: A -> β
            notRecursive.push_back(production);
        }
    }
    
    // Step 2: If no left recursion found, keep original
    if (leftRecursive.empty()) {
        newGrammar[nonTerminal] = grammar[nonTerminal];
        return;
    }
    
    // Step 3: Create new productions
    string newNonTerminal = nonTerminal + "'";  // A becomes A'
    
    // Original non-terminal: A -> β1A' | β2A' | ...
    for (string beta : notRecursive) {
        newGrammar[nonTerminal].push_back(beta + newNonTerminal);
    }
    
    // New non-terminal: A' -> α1A' | α2A' | ... | ε
    for (string alpha : leftRecursive) {
        newGrammar[newNonTerminal].push_back(alpha + newNonTerminal);
    }
    newGrammar[newNonTerminal].push_back("e");  // Add epsilon
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }
    
    // Read number of non-terminals
    int numNonTerminals;
    inputFile >> numNonTerminals;
    inputFile.ignore();
    
    // Read grammar rules
    // Format: "A Aα β1 β2" means A -> Aα | β1 | β2
    for (int i = 0; i < numNonTerminals; i++) {
        string line;
        getline(inputFile, line);
        
        if (line.empty()) {
            i--;
            continue;
        }
        
        stringstream ss(line);
        string nonTerminal;
        ss >> nonTerminal;  // First word is the non-terminal (A, B, E, etc.)
        
        // Rest of the words are productions
        string production;
        while (ss >> production) {
            grammar[nonTerminal].push_back(production);
        }
    }
    inputFile.close();
    
    // Show original grammar
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
    
    // Process each non-terminal to remove left recursion
    cout << "\nRemoving Left Recursion...\n\n";
    for (auto& entry : grammar) {
        removeLeftRecursion(entry.first);
    }
    
    // Show transformed grammar
    cout << "After Removing Left Recursion:\n";
    cout << "================================\n";
    for (auto& entry : newGrammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            if (i > 0) cout << " | ";
            // Show epsilon as ε
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