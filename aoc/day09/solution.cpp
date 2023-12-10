#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day09.txt"
;


int extrapolate(const vector<int> &sequence, bool backwards){
    bool allZero = true;
    for (auto &val: sequence){
        if (val != 0){
            allZero = false;
        }
    }

    if (allZero){
        return 0;
    }

    vector<int> diffs;
    diffs.reserve(sequence.size() - 1);
    for (size_t i = 1; i < sequence.size(); i++){
        diffs.emplace_back(sequence[i] - sequence[i - 1]);

    }

    if (!backwards){
        return sequence[sequence.size() - 1] + extrapolate(diffs, backwards);
    } else {
        return sequence[0] - extrapolate(diffs, backwards);
    }

}

int part1(const vector<vector<int>> &sequences){
    int result = 0;
    for (auto &seq: sequences){
        result += extrapolate(seq, false);
    }

    return result;
}

int part2(const vector<vector<int>> &sequences){
    int result = 0;
    for (auto &seq: sequences){
        result += extrapolate(seq, true);
    }

    return result;
}


void solve(){
    stringstream input(test);

    string line;
    vector<vector<int>> sequences;

    while(getline(input, line)){
        sequences.emplace_back(toIntVec(split(line, " ")));
    }

    cout << "Part 1: " << part1(sequences) << endl;
    cout << "Part 2: " << part2(sequences) << endl;
}
