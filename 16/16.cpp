/**
 * PROBLEM: 16 - Construct LL(1) Parsing Table
 * 
 * ALGORITHM:
 * 1. Compute FIRST sets for all productions
 * 2. Compute FOLLOW sets for all non-terminals
 * 3. Build parsing table M[Non-terminal, Terminal]:
 *    - For A -> α, add to M[A, a] for each a in FIRST(α)
 *    - If ε in FIRST(α), add to M[A, b] for each b in FOLLOW(A)
 */

#include <bits/stdc++.h>
using namespace std;

struct Production {
    string lhs;
    string rhs;
};

vector<Production> grammar;
map<string, set<string>> firstSets;
map<string, set<string>> followSets;
map<pair<string, string>, string> parseTable;
set<string> nonTerminals;
set<string> terminals;
string startSymbol;

// Check if symbol is terminal
bool isTerminal(string symbol) {
    return !isupper(symbol[0]) || symbol == "e" || symbol == "id";
}

// Parse production into symbols
vector<string> parseSymbols(string str) {
    vector<string> symbols;
    int i = 0;
    
    while (i < str.length()) {
        string currentSymbol = "";
        
        if (i + 1 < str.length()) {
            string twoChar = str.substr(i, 2);
            
            if (twoChar == "id") {
                currentSymbol = "id";
                i += 2;
            }
            else if (twoChar[1] == '\'') {
                currentSymbol = twoChar;
                i += 2;
            }
        }
        
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
    if (!firstSets[nonTerminal].empty()) return;
    
    for (auto& prod : grammar) {
        if (prod.lhs != nonTerminal) continue;
        
        vector<string> symbols = parseSymbols(prod.rhs);
        bool allHaveEpsilon = true;
        
        for (string symbol : symbols) {
            if (isTerminal(symbol)) {
                firstSets[nonTerminal].insert(symbol);
                allHaveEpsilon = false;
                break;
            } else {
                computeFirst(symbol);
                
                bool hasEpsilon = false;
                for (string f : firstSets[symbol]) {
                    if (f == "e") {
                        hasEpsilon = true;
                    } else {
                        firstSets[nonTerminal].insert(f);
                    }
                }
                
                if (!hasEpsilon) {
                    allHaveEpsilon = false;
                    break;
                }
            }
        }
        
        if (allHaveEpsilon) {
            firstSets[nonTerminal].insert("e");
        }
    }
}

// Get FIRST of a sequence of symbols
set<string> getFirstOfSequence(vector<string> symbols) {
    set<string> result;
    
    for (string symbol : symbols) {
        if (isTerminal(symbol)) {
            result.insert(symbol);
            return result;
        }
        
        bool hasEpsilon = false;
        for (string f : firstSets[symbol]) {
            if (f == "e") {
                hasEpsilon = true;
            } else {
                result.insert(f);
            }
        }
        
        if (!hasEpsilon) {
            return result;
        }
    }
    
    result.insert("e");
    return result;
}

// Compute FOLLOW sets
void computeFollow() {
    followSets[startSymbol].insert("$");
    
    bool changed = true;
    int iterations = 0;
    
    while (changed && iterations < 10) {
        changed = false;
        iterations++;
        
        for (auto& prod : grammar) {
            string leftSide = prod.lhs;
            vector<string> symbols = parseSymbols(prod.rhs);
            
            for (int i = 0; i < symbols.size(); i++) {
                string currentSymbol = symbols[i];
                
                if (isTerminal(currentSymbol)) continue;
                
                vector<string> beta;
                for (int j = i + 1; j < symbols.size(); j++) {
                    beta.push_back(symbols[j]);
                }
                
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
                    
                    if (hasEpsilon) {
                        for (string f : followSets[leftSide]) {
                            if (followSets[currentSymbol].find(f) == followSets[currentSymbol].end()) {
                                followSets[currentSymbol].insert(f);
                                changed = true;
                            }
                        }
                    }
                } else {
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

// Build parsing table
void buildParseTable() {
    for (auto& prod : grammar) {
        string A = prod.lhs;
        vector<string> alpha = parseSymbols(prod.rhs);
        
        set<string> firstOfAlpha = getFirstOfSequence(alpha);
        
        // For each terminal in FIRST(α)
        for (string a : firstOfAlpha) {
            if (a != "e") {
                parseTable[{A, a}] = prod.rhs;
            }
        }
        
        // If ε in FIRST(α), add for each terminal in FOLLOW(A)
        if (firstOfAlpha.find("e") != firstOfAlpha.end()) {
            for (string b : followSets[A]) {
                parseTable[{A, b}] = prod.rhs;
            }
        }
    }
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error: input.txt not found!" << endl;
        return 1;
    }
    
    int numProductions;
    inputFile >> numProductions;
    inputFile.ignore();
    
    bool isFirst = true;
    for (int i = 0; i < numProductions; i++) {
        string line;
        getline(inputFile, line);
        
        if (line.empty()) {
            i--;
            continue;
        }
        
        stringstream ss(line);
        string lhs, rhs;
        ss >> lhs >> rhs;
        
        if (isFirst) {
            startSymbol = lhs;
            isFirst = false;
        }
        
        Production prod;
        prod.lhs = lhs;
        prod.rhs = rhs;
        grammar.push_back(prod);
        
        nonTerminals.insert(lhs);
        
        // Extract terminals
        vector<string> symbols = parseSymbols(rhs);
        for (string sym : symbols) {
            if (isTerminal(sym) && sym != "e") {
                terminals.insert(sym);
            }
        }
    }
    inputFile.close();
    
    terminals.insert("$");
    
    // Display grammar
    cout << "Grammar:\n";
    cout << "========\n";
    map<string, vector<string>> groupedGrammar;
    for (auto& prod : grammar) {
        groupedGrammar[prod.lhs].push_back(prod.rhs);
    }
    for (auto& entry : groupedGrammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            if (i > 0) cout << " | ";
            cout << entry.second[i];
        }
        cout << "\n";
    }
    
    // Compute FIRST sets
    for (string nt : nonTerminals) {
        computeFirst(nt);
    }
    
    cout << "\nFIRST Sets:\n";
    cout << "===========\n";
    for (auto& entry : firstSets) {
        cout << "FIRST(" << entry.first << ") = { ";
        bool first = true;
        for (string sym : entry.second) {
            if (!first) cout << ", ";
            cout << (sym == "e" ? "ε" : sym);
            first = false;
        }
        cout << " }\n";
    }
    
    // Compute FOLLOW sets
    computeFollow();
    
    cout << "\nFOLLOW Sets:\n";
    cout << "============\n";
    for (string nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        bool first = true;
        for (string sym : followSets[nt]) {
            if (!first) cout << ", ";
            cout << sym;
            first = false;
        }
        cout << " }\n";
    }
    
    // Build parsing table
    buildParseTable();
    
    cout << "\nLL(1) Parsing Table:\n";
    cout << "====================\n\n";
    
    // Calculate column width
    int colWidth = 20;
    
    // Print header
    cout << left << setw(12) << "Non-Term";
    for (string t : terminals) {
        cout << setw(colWidth) << t;
    }
    cout << "\n";
    cout << string(12 + terminals.size() * colWidth, '=') << "\n";
    
    // Print rows
    for (string nt : nonTerminals) {
        cout << left << setw(12) << nt;
        for (string t : terminals) {
            if (parseTable.find({nt, t}) != parseTable.end()) {
                string prod = nt + " -> ";
                if (parseTable[{nt, t}] == "e") {
                    prod += "ε";
                } else {
                    prod += parseTable[{nt, t}];
                }
                cout << setw(colWidth) << prod;
            } else {
                cout << setw(colWidth) << "-";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
