#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day13.txt"
;

int vertCheck(const vector<string>& map, size_t split){
    int smudges = 0;

    for (const auto &row: map){
        for (size_t i = 0; i < min(split, row.size() - split); i++){
            if (row[split - i - 1] != row[split + i]){
                smudges++;
            }
        }
    }

    return smudges;
}

int horCheck(const vector<string>& map, size_t split){
    int smudges = 0;

    for (size_t i = 0; i < min(split, map.size() - split); i++){
        for (size_t j = 0; j < map[split - i - 1].size(); j++){
            char a = map[split - i - 1][j];
            char b = map[split + i][j];
            if (a != b){
                smudges++;
            }
        }
    }

    return smudges;
}

int findReflection(const vector<string> &map, int s){
    int sum = 0;

    for (size_t leftLen = 1; leftLen < map[0].size(); leftLen++){
        int smudges = vertCheck(map, leftLen);

        if (smudges == s){
            sum += leftLen;
            break;
        }
    }

    for (size_t topLen = 1; topLen < map.size(); topLen++){
        int smudges = horCheck(map, topLen);

        if (smudges == s){
            sum += topLen * 100;
            break;
        }
    }

    return sum;
}

int part1(const vector<vector<string>> &map){
    int sum = 0;

    for (const auto &m: map){
        sum += findReflection(m, 0);
    }

    return sum;
}

int part2(const vector<vector<string>> &map){
    int sum = 0;

    for (const auto &m: map){
        sum += findReflection(m, 1);
    }

    return sum;
}

void solve() {
    stringstream input(test);

    string line;
    vector<vector<string>> map;
    map.emplace_back();
    while(getline(input, line)){
        if (line.empty()){
            map.emplace_back();
        } else {
            map[map.size() - 1].emplace_back(line);
        }
    }

    cout << "Part 1: " << part1(map) << endl;
    cout << "Part 2: " << part2(map) << endl;
}
