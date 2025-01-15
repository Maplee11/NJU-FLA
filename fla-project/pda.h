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
public:
    PDA(string pda_file_path) {
        getSymbols(pda_file_path);
    }

    string simulate(string input) {
        string curState = startState;
        std::stack<string> st;
        int ptr = 0;
        st.push(startStackSymbol);
        
        while (ptr != -1) {
            string curSymbol;
            if (ptr == input.size()) {
                curSymbol = "_";
                ptr = -1;
            } else {
                curSymbol = string(1, input[ptr++]);
            }

            if (inputSymbols.find(curSymbol) == inputSymbols.end() && curSymbol != "_") {
                cerr << "illegal input" << endl;
                exit(1);
            } 

            string key = curState + " " + curSymbol + " " + st.top();
            if (delta.find(key) == delta.end()) {
                return "false";
            }

            // cout<<key<<"->"<<delta[key]<<endl;

            auto s = split(' ', delta[key]);
            curState = s[0];
            st.pop();
            if (s[1][0] == '_' && s[1].size() == 1) {
                continue;
            }
            for (int i = s[1].size()-1; i >=0; i--) {
                st.push(string(1, s[1][i]));
            }
        }

        if (finalStates.find(curState) != finalStates.end())
            return "true";
        else
            return "false";
    }

private:
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
                    states = scanSymbols(line);
                }
                if (id == 'S') {
                    inputSymbols = scanSymbols(line);
                }
                if (id == 'G') {
                    stackSymbols = scanSymbols(line);
                }
                if (id == 'F') {
                    finalStates = scanSymbols(line);
                }
                if (line[1] == 'q' && line[2] == '0') {
                    int ptr = line.size() - 1;
                    while (line[ptr] != ' ') ptr--;
                    startState = line.substr(ptr+1, line.size()-ptr-1);
                }
                if (line[1] == 'z' && line[2] == '0') {
                    int ptr = line.size() - 1;
                    while (line[ptr] != ' ') ptr--;
                    startStackSymbol = line.substr(ptr+1, line.size()-ptr-1);
                }
            } else {
                // Get transitions ( , , ) -> ( , )
                std::vector<string> s = split(' ', line);
                delta[s[0] + " " + s[1] + " " + s[2]] = s[3] + " " + s[4];
            }
        }

        file.close();
    }

    std::set<string> scanSymbols(string input) {
        if (input.find('{') == std::string::npos ||
            input.find('}') == std::string::npos) {
            cerr << "syntax error" << endl;
            exit(1);
        }

        int l = 0, r = 0;
        while (input[l] != '{') l++;
        while (input[r] != '}') r++;
        l++, r--;
        auto s = split(',', input.substr(l, r-l+1));
        // cout<<"Scanned: "; for (auto it : s) cout<<it<<" "; cout<<endl;
        return std::set<string>(s.begin(), s.end());
    }

    double a;
    std::unordered_map<string, string> delta;
    string startState, startStackSymbol;
    std::set<string> states, inputSymbols, stackSymbols, finalStates;
};
