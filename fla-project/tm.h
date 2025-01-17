#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stack>
#include <tuple>


using std::string;
using std::cout;
using std::cerr;
using std::endl;

typedef std::pair<string, string> Pa;
typedef std::tuple<string, string, string> Tup;


std::vector<string> split(char spliter, string input);


namespace std {
    template <>
    struct hash<std::pair<string, string>> {
        size_t operator()(const std::pair<string, string>& p) const {
            size_t h1 = hash<string>()(p.first);
            size_t h2 = hash<string>()(p.second);
            return h1 ^ (h2 << 1);
        }
    };
}


class TM {
    std::unordered_map<Pa, Tup> delta;
    string startState;
    char blankSymbol;
    std::set<string> states, inputSymbols, tapeSymbols, haltStates;
    std::map<int, char>* tape;
    int* head;
    int tapeNum;
    bool verbose;

public:
    TM(string tm_file_path, bool verbose_) : verbose(verbose_) {
        decodeFileTM(tm_file_path);
        while (clearStarTransaction());
        tape = new std::map<int, char>[tapeNum];
        head = new int[tapeNum]();
    }

    ~TM() {
        delete [] tape;
        delete [] head;
    }

    string simulate(string input) {
        checkInput(input);
        verboseInitial(input);
        tapeInitialize(input);

        string curState = startState, newSymbols, moves, nxtState;

        for (int step = 0; ; step++) {
            printState(step, curState);
            Pa key = Pa(curState, readAllSymbols());

            if (delta.find(key) == delta.end()) {
                return replaceSpace(getTapeContent(0));
            }

            Tup val = delta[key];

            newSymbols = std::get<0>(val);
            moves = std::get<1>(val);
            nxtState = std::get<2>(val);

            writeAllTapes(newSymbols);
            moveAllHeads(moves);
            curState = nxtState;

            // cout << curState << newSymbols << " " << moves << " " << nxtState << endl;
        }

        return "Cannot reach here";
    }

private:
    void printState(int step, string curState) {
        if (!verbose) return;
        cout << "Step   : " << step << endl;
        cout << "State  : " << curState << endl;

        for (int i = 0; i < tapeNum; i++) {
            auto& tp = tape[i];

            cout << "Index" << i << " : ";
            int l = head[i], r = head[i];
            while (tp.find(l-1) != tp.end()) l--;
            while (tp.find(r+1) != tp.end()) r++;
            while (tp[l] == blankSymbol && l < head[i]) l++;
            while (tp[r] == blankSymbol && r > head[i]) r--;
            for (int j = l; j <= r; j++) {
                cout << std::max(j, -j) << " ";
            }
            cout << endl;

            cout << "Tape" << i << "  : ";
            for (int j = l; j <= r; j++) {
                cout << tp[j] << " ";
                if (std::max(j, -j) >= 10) cout << " ";
                if (std::max(j, -j) >= 100) cout << " ";
            }
            cout << endl;

            cout << "Head" << i << "  : ";
            int alignOffset = 0;
            for (int j = l; j < head[i]; j++) {
                alignOffset += ((std::max(j, -j) >= 10) + (std::max(j, -j) >= 100));
            }
            for (int j = 0; j < 2*(head[i]-l)+alignOffset; j++) {
                cout << " ";
            }
            cout << "^" << endl;
        }

        cout << "---------------------------------------------" << endl;
    }

    bool clearStarTransaction() {
        for (auto it = delta.begin(); it != delta.end(); it++) {
            Pa key = it->first;
            Tup val = it->second;
            int pos = key.second.find('*');
            if (pos != string::npos) {
                delta.erase(key);
                for (string c : tapeSymbols) {
                    if (c[0] == '_') continue;
                    key.second[pos] = c[0];
                    delta[key] = val;
                    // cout << "Add: " << key.first << " " << key.second << " " << std::get<0>(val) << " " << std::get<1>(val) << " " << std::get<2>(val) << endl;
                }
                return true;
            }
        }
        return false;
    }

    void moveLeft(int tapeIdx) {
        auto& tp = tape[tapeIdx];
        --head[tapeIdx];
        if (tp.find(head[tapeIdx]) == tp.end()) {
            tp[head[tapeIdx]] = blankSymbol;
        }
    }

    void moveRight(int tapeIdx) {
        auto& tp = tape[tapeIdx];
        ++head[tapeIdx];
        if (tp.find(head[tapeIdx]) == tp.end()) {
            tp[head[tapeIdx]] = blankSymbol;
        }
    }

    void moveAllHeads(string& moves) {
        for (int i = 0; i < tapeNum; i++) {
            if (moves[i] == 'l') {
                moveLeft(i);
            }
            if (moves[i] == 'r') {
                moveRight(i);
            }
        }
    }

    void moveHead(int tapeIdx, int offset) {
        head[tapeIdx] += offset;
    }

    void writeAllTapes(string& symbols) {
        for (int i = 0; i < tapeNum; i++) {
            write(i, symbols[i]);
        }
    }

    void write(int tapeIdx, char c) {
        if (c != '*') {
            tape[tapeIdx][head[tapeIdx]] = c;
        }
    }

    char read(int tapeIdx) {
        return tape[tapeIdx][head[tapeIdx]];
    }

    string readAllSymbols() {
        string ret = "";
        for (int i = 0; i < tapeNum; i++) {
            ret.push_back(read(i));
        }
        return ret;
    }

    void decodeFileTM(string pda_file_path) {
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
                    tapeSymbols = scanSymbols(line);
                }
                if (line[1] == 'q' && line[2] == '0') {
                    startState = line.substr(6, string::npos);
                }
                if (id == 'B') {
                    blankSymbol = (line.substr(5, string::npos))[0];
                }
                if (id == 'F') {
                    haltStates = scanSymbols(line);
                }
                if (id == 'N') {
                    tapeNum = std::stoi(line.substr(5, string::npos));
                }
            } else {
                // Get transitions ( , , ) -> ( , )
                std::vector<string> s = split(' ', line);
                delta[Pa(s[0], s[1])] = Tup(s[2], s[3], s[4]);
            }
        }

        file.close();

        if (inputSymbols.find("*") != inputSymbols.end() || tapeSymbols.find("*") != tapeSymbols.end()) {
            cerr << "syntax error" << endl;
            exit(1);
        }
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

    void verboseInitial(string& input) {
        if (verbose) {
            cout << "Input: " << input << endl;
            cout << "==================== RUN ====================" << endl;
        }
    }

    void tapeInitialize(string& input) {
        for (int i = 0; i < tapeNum; i++) {
            tape[i][0] = blankSymbol;
        }

        for (int i = 0; i < int(input.size()); i++) {
            tape[0][i] = input[i];
        }
    }

    string getTapeContent(int num) {
        std::map<int, char>& tp = tape[num];
        string ret = "";

        if (!tp.empty()) {
            int l = tp.begin()->first, r = tp.rbegin()->first;
            while (tp[l] == blankSymbol) l++;
            while (tp[r] == blankSymbol) r--;
            for (int i = l; i <= r; i++) {
                ret.push_back(tp[i]);
            }
        }

        return ret;
    }

    string replaceSpace(const string& input) {
        string ret = input;
        for (char& c : ret) {
            if (c == '_') {
                c = ' ';
            }
        }
        return ret;
    }
};
