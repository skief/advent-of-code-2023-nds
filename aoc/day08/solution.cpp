#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <tuple>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day08.txt"
;

enum Direction {
    LEFT = 0,
    RIGHT
};

class Map{
public:
    vector<Direction> instructions;
    map<string, tuple<string, string>> nodes;

    void setInstr(const string& instr){
        instructions.clear();
        instructions.reserve(instr.size());
        for (size_t i = 0; i < instr.size(); i++){
            if (instr[i] == 'R'){
                instructions.emplace_back(RIGHT);
            } else {
                instructions.emplace_back(LEFT);
            }
        }
    }

    void add(const string& line){
        nodes[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }

    int steps(string pos, bool ghost) const{
        int step = 0;

        while ((!ghost && pos != "ZZZ") || (ghost && pos[2] != 'Z')){
            if (instructions[step % instructions.size()] == LEFT){
                pos = get<0>(nodes.at(pos));
            } else {
                pos = get<1>(nodes.at(pos));
            }
            step++;
        }

        return step;
    }
};

int part1(const Map &map){
    return map.steps("AAA", false);
}

int64_t part2(const Map &map){
    vector<int> steps;
    for (auto &[key, val]: map.nodes){
        if (key[2] == 'A'){
            steps.emplace_back(map.steps(key, true));
        }
    }

    int64_t multiple = 1;
    for (auto &step: steps){
        multiple = lcm(multiple, step);
    }

    return multiple;
}


void solve(){
    stringstream input(test);

    string line;
    Map map;
    getline(input, line);
    map.setInstr(line);
    getline(input, line);

    while(getline(input, line)){
        map.add(line);
    }

    cout << "Part 1: " << part1(map) << endl;
    cout << "Part 2: " << part2(map) << endl;
}
