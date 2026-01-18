/**
 * PROBLEM: 17. Write a C++ program for constructing of LL(1) parsing
 */

#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> grammar;
map<pair<string, string>, string> parsingTable;
map<string, set<string>> firstSet, followSet;
string startSymbol;

/* Check if symbol is terminal */
bool isTerminal(const string &s)
{
    return s != "e" && !isupper(s[0]);
}

/* Split production into symbols (handle id, E', T') */
vector<string> splitSymbols(const string &prod)
{
    vector<string> symbols;
    for (size_t i = 0; i < prod.size();)
    {
        if (i + 1 < prod.size() && prod[i] == 'i' && prod[i + 1] == 'd')
        {
            symbols.push_back("id");
            i += 2;
        }
        else if (i + 1 < prod.size() && prod[i + 1] == '\'')
        {
            symbols.push_back(prod.substr(i, 2));
            i += 2;
        }
        else
        {
            symbols.push_back(string(1, prod[i]));
            i++;
        }
    }
    return symbols;
}

/* ---------- FIRST ---------- */
void findFirst(string symbol)
{
    if (!firstSet[symbol].empty())
        return;

    for (string prod : grammar[symbol])
    {
        if (prod == "e")
        {
            firstSet[symbol].insert("e");
            continue;
        }

        vector<string> symbols = splitSymbols(prod);
        bool allEpsilon = true;

        for (string s : symbols)
        {
            if (isTerminal(s))
            {
                firstSet[symbol].insert(s);
                allEpsilon = false;
                break;
            }
            else
            {
                findFirst(s);
                bool hasEpsilon = false;
                for (string c : firstSet[s])
                {
                    if (c == "e")
                        hasEpsilon = true;
                    else
                        firstSet[symbol].insert(c);
                }
                if (!hasEpsilon)
                {
                    allEpsilon = false;
                    break;
                }
            }
        }

        if (allEpsilon)
            firstSet[symbol].insert("e");
    }
}

/* ---------- FOLLOW ---------- */
void findFollow()
{
    followSet[startSymbol].insert("$");
    bool changed;

    do
    {
        changed = false;
        for (auto g : grammar)
        {
            string A = g.first;
            for (string prod : g.second)
            {
                if (prod == "e")
                    continue;

                vector<string> symbols = splitSymbols(prod);
                for (size_t i = 0; i < symbols.size(); i++)
                {
                    string B = symbols[i];
                    if (isTerminal(B))
                        continue;

                    bool epsilonInBeta = true;

                    for (size_t j = i + 1; j < symbols.size(); j++)
                    {
                        string next = symbols[j];
                        if (isTerminal(next))
                        {
                            changed |= followSet[B].insert(next).second;
                            epsilonInBeta = false;
                            break;
                        }
                        else
                        {
                            for (string c : firstSet[next])
                            {
                                if (c != "e")
                                    changed |= followSet[B].insert(c).second;
                            }
                            if (firstSet[next].count("e") == 0)
                            {
                                epsilonInBeta = false;
                                break;
                            }
                        }
                    }

                    if (epsilonInBeta)
                    {
                        for (string c : followSet[A])
                            changed |= followSet[B].insert(c).second;
                    }
                }
            }
        }
    } while (changed);
}

/* ---------- Build Parsing Table ---------- */
void buildParsingTable()
{
    for (auto g : grammar)
    {
        string A = g.first;
        for (string prod : g.second)
        {
            set<string> symbols;

            if (prod == "e")
            {
                symbols = followSet[A];
            }
            else
            {
                vector<string> prodSymbols = splitSymbols(prod);
                string firstSym = prodSymbols[0];

                if (isTerminal(firstSym))
                {
                    symbols.insert(firstSym);
                }
                else
                {
                    for (string c : firstSet[firstSym])
                    {
                        if (c != "e")
                            symbols.insert(c);
                    }
                    if (firstSet[firstSym].count("e"))
                    {
                        for (string c : followSet[A])
                            symbols.insert(c);
                    }
                }
            }

            for (string terminal : symbols)
                parsingTable[{A, terminal}] = prod;
        }
    }
}

/* ---------- Predictive Parser ---------- */
void parseString(const string &inputStr)
{
    vector<string> input;

    // Tokenize input (handle "id" as single token)
    for (size_t i = 0; i < inputStr.size();)
    {
        if (i + 1 < inputStr.size() && inputStr[i] == 'i' && inputStr[i + 1] == 'd')
        {
            input.push_back("id");
            i += 2;
        }
        else
        {
            input.push_back(string(1, inputStr[i]));
            i++;
        }
    }
    input.push_back("$");

    stack<string> st;
    st.push("$");
    st.push(startSymbol);

    int ptr = 0;
    cout << "\nParsing Steps:\n";

    while (!st.empty())
    {
        string top = st.top();
        string a = input[ptr];

        if (top == a)
        {
            if (top == "$")
            {
                cout << "String accepted!\n";
                return;
            }
            st.pop();
            ptr++;
        }
        else if (isTerminal(top))
        {
            cout << "Error: Unexpected symbol " << a << endl;
            cout << "String rejected!\n";
            return;
        }
        else
        {
            if (parsingTable.count({top, a}) == 0)
            {
                cout << "Error: No rule for " << top << " with input " << a << endl;
                cout << "String rejected!\n";
                return;
            }
            else
            {
                st.pop();
                string prod = parsingTable[{top, a}];
                cout << top << " -> " << prod << endl;

                if (prod != "e")
                {
                    vector<string> symbols = splitSymbols(prod);
                    for (int i = symbols.size() - 1; i >= 0; i--)
                        st.push(symbols[i]);
                }
            }
        }
    }
}

/* ---------- MAIN ---------- */
int main()
{
    ifstream file("input.txt");
    if (!file)
    {
        cout << "Error: input.txt not found\n";
        return 0;
    }

    int n;
    file >> n;

    for (int i = 0; i < n; i++)
    {
        string lhs, rhs;
        file >> lhs >> rhs;
        grammar[lhs].push_back(rhs);
        if (i == 0)
            startSymbol = lhs;
    }

    string inputString;
    file >> inputString;
    file.close();

    for (auto g : grammar)
        findFirst(g.first);
    findFollow();
    buildParsingTable();

    cout << "Input string: " << inputString << endl;
    parseString(inputString);

    return 0;
}
