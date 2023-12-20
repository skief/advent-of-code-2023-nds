#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day19.txt"
;

struct State {int xmas[4];};

class Instruction{
public:
    int variable;
    char operation;
    int value;
    string workflow;

    Instruction(const string &instr){
        switch (instr[0]) {
            case 'x': variable = 0; break;
            case 'm': variable = 1; break;
            case 'a': variable = 2; break;
            case 's': variable = 3; break;
        }

        operation = instr[1];
        size_t pos = instr.find(':');

        value = stoi(instr.substr(2, pos - 2));
        workflow = instr.substr(pos + 1);
    }

    bool applies(const State &part) const{
        if (operation == '<'){
            return part.xmas[variable] < value;
        } else {
            return part.xmas[variable] > value;
        }
    };
};

class Workflow{
public:
    vector<Instruction> instructions;
    string w;

    Workflow(){}
    Workflow(const string &workflow){
        vector<string> instr = split(workflow, ",");
        for (size_t i = 0; i < instr.size() - 1; i++){
            instructions.emplace_back(instr[i]);
        }
        w = instr[instr.size() - 1];
    }

    string apply(const State &part) const{
        for (const auto &instr: instructions){
            if (instr.applies(part)){
                return instr.workflow;
            }
        }

        return w;
    }
};

int64_t part1(const map<string, Workflow> &workflows, const vector<State> &parts){
    int64_t accepted = 0;

    for (const auto &part: parts){
        string w = "in";
        while (w != "A" && w != "R"){
            w = workflows.at(w).apply(part);
        }
        if (w == "A"){
            accepted += part.xmas[0] + part.xmas[1] + part.xmas[2] + part.xmas[3];
        }

    }

    return accepted;
}

int64_t countAcceptedStates(const map<string, Workflow> &map, const string &w, State lower, State upper){
    for (size_t i = 0; i < 4; i++){
        if (lower.xmas[i] > upper.xmas[i]){
            return 0;
        }
    }

    if (w == "R"){
        return 0;
    }
    if (w == "A"){
        int64_t diffs[4];

        for (size_t i = 0; i < 4; i++){
            diffs[i] = upper.xmas[i] - lower.xmas[i] + 1;
        }

        return diffs[0] * diffs[1] * diffs[2] * diffs[3];
    }

    int64_t total = 0;

    for (const auto &instr: map.at(w).instructions){
        if (instr.operation == '<'){
            State newUpper{{upper.xmas[0], upper.xmas[1], upper.xmas[2], upper.xmas[3]}};

            newUpper.xmas[instr.variable] = instr.value - 1;
            total += countAcceptedStates(map, instr.workflow, lower, newUpper);
            lower.xmas[instr.variable] = instr.value;
        } else {
            State newLower{{lower.xmas[0], lower.xmas[1], lower.xmas[2], lower.xmas[3]}};

            newLower.xmas[instr.variable] = instr.value + 1;
            total += countAcceptedStates(map, instr.workflow, newLower, upper);
            upper.xmas[instr.variable] = instr.value;
        }
    }

    return total + countAcceptedStates(map, map.at(w).w, lower, upper);
}

int64_t part2(const map<string, Workflow> &workflows){
    return countAcceptedStates(workflows, "in", State{{1, 1, 1, 1}}, State{{4000, 4000, 4000, 4000}});
}

void solve(){
    stringstream input(test);

    string line;
    map<string, Workflow> workflows;
    vector<State> parts;

    while(getline(input, line)){
        if (line.empty()){
            break;
        }

        size_t pos = line.find('{');
        workflows[line.substr(0, pos)] = Workflow(line.substr(pos + 1, line.length() - pos - 2));
    }

    while(getline(input, line)){
        size_t pos = line.find('=');
        size_t pos2 = line.find(',', pos);
        int x = stoi(line.substr(pos + 1, pos2 - pos - 1));

        pos = line.find('=', pos2);
        pos2 = line.find(',', pos);
        int m = stoi(line.substr(pos + 1, pos2 - pos - 1));

        pos = line.find('=', pos2);
        pos2 = line.find(',', pos);
        int a = stoi(line.substr(pos + 1, pos2 - pos - 1));

        pos = line.find('=', pos2);
        pos2 = line.find('}', pos);
        int s = stoi(line.substr(pos + 1, pos2 - pos - 1));

        parts.emplace_back(State{{x, m, a, s}});
    }

    cout << "Part 1: " << part1(workflows, parts) << endl;
    cout << "Part 2: " << part2(workflows) << endl;
}
