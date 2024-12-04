#include <iostream>
#include <pda.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

std::vector<string> split(char spliter, string input) {
    std::vector<string> ret;
    int l = 0, r = 0;
    while (r != input.size()) {
        r = l;
        while (r != input.size() && input[r] != spliter) r++;
        ret.push_back(input.substr(l, r-l));
        l = r + 1;
    }
    return ret;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Too few arguements." << endl;
        return 0;
    }

    string ext = split('.', argv[1]).back();
    string input_file = argv[1];
    string input_str = argv[2];

    if (ext == "pda") {
        PDA pda(input_file);
        cout << pda.simulate(input_str) << endl;
    }
    else if (ext == "tm") {
        cerr << "Undone" <<endl;
    }
    else {
        cerr << "Invalid input file extension." << endl;
    }

    return 0;
}
/*

./run.sh ../pda/anbn.pda aaabbb

*/