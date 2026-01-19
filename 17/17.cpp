/**
 * PROBLEM: 17 - LL(1) Parsing (All logic in main)
 * INPUT: Hardcoded "id+id"
 * OUTPUT: Parsing Table & Steps
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 1. DATA STRUCTURES
    // Map: { {NonTerminal, Terminal} -> Production Rule }
    map<pair<string, string>, string> table;

    // 2. HARDCODE THE PARSING TABLE
    // Grammar:
    // E -> TE'
    // E' -> +TE' | e
    // T -> FT'
    // T' -> *FT' | e
    // F -> (E) | id

    // Row E
    table[{"E", "id"}] = "TE'";
    table[{"E", "("}]  = "TE'";

    // Row E'
    table[{"E'", "+"}] = "+TE'";
    table[{"E'", ")"}] = "e";
    table[{"E'", "$"}] = "e";

    // Row T
    table[{"T", "id"}] = "FT'";
    table[{"T", "("}]  = "FT'";

    // Row T'
    table[{"T'", "+"}] = "e";
    table[{"T'", "*"}] = "*FT'";
    table[{"T'", ")"}] = "e";
    table[{"T'", "$"}] = "e";

    // Row F
    table[{"F", "id"}] = "id";
    table[{"F", "("}]  = "(E)";

    // 3. PREPARE INPUT
    string inputRaw = "id+id";
    vector<string> input;
    
    // Manual tokenization of input string (id+id -> id, +, id, $)
    for (int i = 0; i < inputRaw.length(); i++) {
        if (inputRaw[i] == 'i' && inputRaw[i+1] == 'd') {
            input.push_back("id");
            i++; // skip 'd'
        } else {
            string s(1, inputRaw[i]);
            input.push_back(s);
        }
    }
    input.push_back("$"); // End marker

    // 4. INITIALIZE STACK
    stack<string> st;
    st.push("$");
    st.push("E"); // Start Symbol

    // 5. PARSING LOOP
    int ptr = 0; // Pointer for input
    
    cout << "Parsing String: " << inputRaw << "\n\n";
    cout << left << setw(20) << "STACK" << setw(20) << "INPUT" << "ACTION" << endl;
    cout << "------------------------------------------------------------" << endl;

    while (!st.empty()) {
        string top = st.top();
        string currentInput = input[ptr];

        // --- DISPLAY LOGIC ---
        // Construct stack string for display
        stack<string> tempSt = st;
        string stackStr = "";
        while(!tempSt.empty()) {
            stackStr = tempSt.top() + stackStr;
            tempSt.pop();
        }
        
        // Construct input string for display
        string inputStr = "";
        for(int i = ptr; i < input.size(); i++) inputStr += input[i];

        cout << left << setw(20) << stackStr << setw(20) << inputStr;

        // --- PARSING LOGIC ---
        
        // Case 1: Match Found
        if (top == currentInput) {
            if (top == "$") {
                cout << "ACCEPTED" << endl;
                break;
            }
            cout << "Match " << currentInput << endl;
            st.pop();
            ptr++;
        }
        // Case 2: Non-Terminal on Stack (Lookup Table)
        else if (isupper(top[0])) { // Simple check for Non-Terminal
            if (table.find({top, currentInput}) != table.end()) {
                string production = table[{top, currentInput}];
                cout << top << " -> " << production << endl;
                st.pop();

                // Push production to stack in REVERSE order
                if (production != "e") {
                    for (int i = production.length() - 1; i >= 0; i--) {
                        string symbol = "";
                        
                        // Handle ' (prime)
                        if (production[i] == '\'') {
                            symbol = production.substr(i-1, 2); // Get "E'" or "T'"
                            i--; // Skip the letter before '
                        }
                        // Handle id
                        else if (production[i] == 'd' && i > 0 && production[i-1] == 'i') {
                            symbol = "id";
                            i--; // Skip 'i'
                        }
                        // Handle single characters
                        else {
                            symbol = string(1, production[i]);
                        }
                        st.push(symbol);
                    }
                }
            } else {
                cout << "Error: No rule for [" << top << ", " << currentInput << "]" << endl;
                return 0;
            }
        }
        // Case 3: Mismatch
        else {
            cout << "Error: Unexpected symbol" << endl;
            return 0;
        }
    }

    return 0;
}