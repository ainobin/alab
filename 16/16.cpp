/**
 * PROBLEM: Construct LL(1) Parsing Table (Hardcoded Data)
 * OUTPUT: Clean Table Only (No decorations)
 */

#include <bits/stdc++.h>
using namespace std;

// --- Data Structures ---
struct Production {
    string lhs;
    vector<string> rhs; 
    string rhsString;   
};

vector<Production> grammar;
map<string, set<string>> firstSets;
map<string, set<string>> followSets;
map<pair<string, string>, string> parseTable;
set<string> terminals;
vector<string> nonTerminals; // Changed to vector to keep order E, E', T, T', F

// --- Helper Functions ---
bool isTerminal(string symbol) {
    return !(isupper(symbol[0]));
}

set<string> getFirstOfRHS(const vector<string>& rhs) {
    set<string> result;
    if (rhs.size() == 1 && rhs[0] == "e") {
        result.insert("e");
        return result;
    }
    for (const string& symbol : rhs) {
        if (isTerminal(symbol)) {
            result.insert(symbol);
            return result;
        }
        bool hasEpsilon = false;
        for (const string& f : firstSets[symbol]) {
            if (f == "e") hasEpsilon = true;
            else result.insert(f);
        }
        if (!hasEpsilon) return result;
    }
    result.insert("e");
    return result;
}

int main() {
    // 1. HARDCODE DATA
    grammar.push_back({"E",  {"T", "E'"},   "TE'"});
    grammar.push_back({"E'", {"+", "T", "E'"}, "+TE'"});
    grammar.push_back({"E'", {"e"},         "e"});
    grammar.push_back({"T",  {"F", "T'"},   "FT'"});
    grammar.push_back({"T'", {"*", "F", "T'"}, "*FT'"});
    grammar.push_back({"T'", {"e"},         "e"});
    grammar.push_back({"F",  {"(", "E", ")"}, "(E)"});
    grammar.push_back({"F",  {"id"},        "id"});

    // Use vector for specific print order
    nonTerminals = {"E", "E'", "T", "T'", "F"};
    terminals = {"id", "+", "*", "(", ")", "$"};

    firstSets["E"]  = {"(", "id"};
    firstSets["E'"] = {"+", "e"};
    firstSets["T"]  = {"(", "id"};
    firstSets["T'"] = {"*", "e"};
    firstSets["F"]  = {"(", "id"};
    firstSets["e"]  = {"e"}; firstSets["id"] = {"id"}; firstSets["+"] = {"+"};
    firstSets["*"]  = {"*"}; firstSets["("] = {"("}; firstSets[")"] = {")"};

    followSets["E"]  = {")", "$"};
    followSets["E'"] = {")", "$"};
    followSets["T"]  = {"+", ")", "$"};
    followSets["T'"] = {"+", ")", "$"};
    followSets["F"]  = {"*", "+", ")", "$"};

    // 2. BUILD TABLE
    for (const auto& prod : grammar) {
        string A = prod.lhs;
        set<string> firstAlpha = getFirstOfRHS(prod.rhs);

        for (const string& a : firstAlpha) {
            if (a != "e") parseTable[{A, a}] = prod.rhsString;
        }
        if (firstAlpha.count("e")) {
            for (const string& b : followSets[A]) parseTable[{A, b}] = prod.rhsString;
        }
    }

    // 3. PRINT TABLE (Clean Format)
    int colWidth = 12;

    // Header
    cout << left << setw(colWidth) << " "; // Empty corner
    for (const string& t : terminals) {
        cout << setw(colWidth) << t;
    }
    cout << "\n";

    // Rows
    for (const string& nt : nonTerminals) {
        cout << left << setw(colWidth) << nt;
        for (const string& t : terminals) {
            if (parseTable.count({nt, t})) {
                string s = nt + "->" + parseTable[{nt, t}];
                if (parseTable[{nt, t}] == "e") s = nt + "->e"; // Display epsilon as 'e'
                cout << setw(colWidth) << s;
            } else {
                cout << setw(colWidth) << ""; // Print empty space if no rule
            }
        }
        cout << "\n";
    }

    return 0;
}