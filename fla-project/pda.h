#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stack>


using std::string;
using std::cout;
using std::cerr;
using std::endl;

std::vector<string> split(char spliter, string input);


class PDA {
    std::unordered_map<string, string> delta;
    string startState, startStackSymbol;
    std::set<string> states, inputSymbols, stackSymbols, finalStates;
    bool verbose;

public:
    PDA(string pda_file_path, bool verbose_) : verbose(verbose_) {
        getSymbols(pda_file_path);
    }

    void simulate(string input) {
        string res = getResult(input);
        if (verbose) cout << "Result: ";
        cout << res << endl;
        if (verbose) cout << "==================== END ====================" << endl;
    }

private:
    string getResult(string& input) {
        checkInput(input);
        verboseInitial(input);

        string curState = startState;
        std::stack<string> st({startStackSymbol});
        int ptr = 0, step = 0;

        while (1) {
            printState(curState, ptr, step++, st, input);

            if (finalStates.find(curState) != finalStates.end())
                return "true";

            if (st.empty()) {
                return "false";
            }

            string curSymbol = (ptr == input.size()) ? "_" : string(1, input[ptr++]);
            string key = curState + " " + curSymbol + " " + st.top();

            if (delta.find(key) == delta.end()) {
                return "false";
            }

            auto s = split(' ', delta[key]);
            curState = s[0];
            st.pop();

            if (s[1][0] != '_') {
                for (int i = s[1].size()-1; i >=0; i--) {
                    st.push(string(1, s[1][i]));
                }
            }
        }

        return "Cannot reach here";
    }
    
    void printState(string curState, int ptr, int step, std::stack<string> st, string input) {
        if (!verbose) return;
        cout << "Step   : " << step << endl;
        cout << "State  : " << curState << endl;
        
        cout << "Stack  : ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;

        cout << "Input  : " << input;
        if (ptr == int(input.size())) cout << "_";
        cout << endl;
        cout << "Head   : ";
        for (int _ = 0; _ < ptr; _++) cout << " ";
        cout << "^" << endl;

        cout << "---------------------------------------------" << endl;
    }

    void verboseInitial(string& input) {
        if (verbose) {
            cout << "Input: " << input << endl;
            cout << "==================== RUN ====================" << endl;
        }
    }

    void checkInput(string& input) {
        for (int i = 0; i < int(input.size()); i++) {
            char c = input[i];
            if (inputSymbols.find(string(1, c)) == inputSymbols.end()) {
                if (!verbose) {
                    cerr << "illegal input" << endl;
                    exit(1);
                }
                cerr << "Input: " << input << endl;
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: " << "'" << c << "'" << " was not declared in the set of input symbols" << endl;
                cerr << "Input: " << input << endl;
                for (int _ = 0; _ < i + 7; _++) cerr << " "; cerr << "^" << endl;
                cerr << "==================== END ====================" << endl;
                exit(1);
            }
        }
    }

    void getSymbols(string pda_file_path) {
        std::ifstream file(pda_file_path);
        string line;

        if (!file) {
            cerr << "File doesn't exist." << endl;
            exit(1);
        }

        // Get states, symbols and transitions
        while (std::getline(file, line)) {
            if (line[0] == ';' || line.empty())
                continue;

            if (line[0] == '#') {
                char id = line[1];
                if (id == 'Q') {
                    if (!states.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    states = scanSymbols(line);
                }
                else if (id == 'S') {
                    if (!inputSymbols.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    inputSymbols = scanSymbols(line);
                }
                else if (id == 'G') {
                    if (!stackSymbols.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    stackSymbols = scanSymbols(line);
                }
                else if (id == 'F') {
                    if (!finalStates.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    finalStates = scanSymbols(line);
                }
                else if (line[1] == 'q' && line[2] == '0') {
                    if (!startState.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    int ptr = line.size() - 1;
                    while (line[ptr] != ' ') ptr--;
                    startState = line.substr(ptr+1, line.size()-ptr-1);
                }
                else if (line[1] == 'z' && line[2] == '0') {
                    if (!startStackSymbol.empty()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                    int ptr = line.size() - 1;
                    while (line[ptr] != ' ') ptr--;
                    startStackSymbol = line.substr(ptr+1, line.size()-ptr-1);
                }
                else {
                    cerr << "syntax error" << endl;
                    exit(1);
                }
            } else {
                // Get transitions ( , , ) -> ( , )
                std::vector<string> s = split(' ', line);
                if (
                        s.size() < 5 || \
                        states.find(s[0]) == states.end() || \
                        states.find(s[3]) == states.end() || \
                        (s[1] != "_" && inputSymbols.find(s[1]) == inputSymbols.end()) || \
                        (s[2] != startStackSymbol && stackSymbols.find(s[2]) == stackSymbols.end()) \
                    ) {
                    cerr << "syntax error" << endl;
                    exit(1);
                }
                
                for (char c : s[4]) {
                    if (c != '_' && string(1, c) != startStackSymbol && stackSymbols.find(string(1, c)) == stackSymbols.end()) {
                        cerr << "syntax error" << endl;
                        exit(1);
                    }
                }

                delta[s[0] + " " + s[1] + " " + s[2]] = s[3] + " " + s[4];
            }
        }

        file.close();

        for (string s : inputSymbols) {
            if (s.size() != 1) {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }

        for (string s : stackSymbols) {
            if (s.size() != 1) {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }

        for (string s : finalStates) {
            if (states.find(s) == states.end()) {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }
    }

    std::set<string> scanSymbols(string input) {
        int l = input.find('{'), r = input.find('}');
        if (l == string::npos || r == string::npos) {
            cerr << "syntax error" << endl;
            exit(1);
        }

        l++, r--;
        auto s = split(',', input.substr(l, r-l+1));
        return std::set<string>(s.begin(), s.end());
    }
};
