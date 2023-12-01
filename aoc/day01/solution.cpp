#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

constexpr char *test =
#include "../../inputs/day01.txt"
;

extern void wait(int seconds);

int getNumber(const string& line, const map<string, int>& numbers){
    size_t first_pos = line.length();
    int first_val = -1;
    size_t last_pos = 0;
    int last_val = -1;

    for (auto [str, val]: numbers){
        size_t pos = line.find(str);
        if (pos != string::npos && pos < first_pos){
            first_pos = pos;
            first_val = val;
        }

        pos = line.rfind(str);
        if (pos != string::npos && pos > last_pos){
            last_pos = pos;
            last_val = val;
        }
    }

    return 10 * first_val + last_val;
}

void solve(){
    stringstream input(test);

    string line;

    vector<string> lines;
    while (getline(input, line)){
        lines.emplace_back(line);
    }

    map<string, int> validNumbers;
    for (int i = 1; i < 10; i++){
        validNumbers[to_string(i)] = i;
    }

    int part1 = 0;
    for (auto line: lines){
        part1 += getNumber(line, validNumbers);
    }

    cout << "Part 1: " << part1 << endl;

    // wait(2);

    validNumbers["one"] = 1;
    validNumbers["two"] = 2;
    validNumbers["three"] = 3;
    validNumbers["four"] = 4;
    validNumbers["five"] = 5;
    validNumbers["six"] = 6;
    validNumbers["seven"] = 7;
    validNumbers["eight"] = 8;
    validNumbers["nine"] = 9;

    int part2 = 0;
    for (auto line: lines){
        part2 += getNumber(line, validNumbers);
    }

    cout << "Part 2: " << part2 << endl;
}
