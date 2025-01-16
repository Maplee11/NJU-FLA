#include <iostream>
#include <pda.h>
#include <tm.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

std::vector<string> split(char spliter, string input) {
    if (input.find(string(string(1, spliter))) == string::npos) {
        return {input};
    }

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
    if (argc < 2) {
        cerr << "Too few arguements." << endl;
        return 1;
    }

    bool verbose = false;
    int offset = 1;

    if (string(argv[1]) == "-h" || string(argv[1]) == "--help") {
        cout << "usage:   fla [-h|--help] <pda> <input>" << endl;
        cout << "         fla [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        return 0;
    }

    if (string(argv[1]) == "-v" || string(argv[1]) == "--verbose") {
        verbose = true;
        offset++;
    }

    if (argc - offset < 2) {
        cerr << "Too few arguements." << endl;
        return 1;
    }

    string ext = split('.', argv[offset]).back();
    string input_file = argv[offset];
    string input_str = argv[offset+1];

    if (ext == "pda") {
        PDA pda(input_file);
        cout << pda.simulate(input_str) << endl;
    }
    else if (ext == "tm") {
        TM tm(input_file, verbose);
        string res = tm.simulate(input_str);
        if (verbose) cout << "Result: ";
        cout << res << endl;
        if (verbose) cout << "==================== END ====================" << endl;
    }
    else {
        cerr << "Invalid input file extension." << endl;
    }

    return 0;
}
/*

./run.sh ../pda/anbn.pda aaabbb

*/