#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <inttypes.h>
#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day12.txt"
;


enum State{
    OPERATIONAL,
    DAMAGED,
    UNKNOWN
};

int64_t combinations(vector<vector<int64_t>> &dp, size_t pos, size_t groupPos,
                     const vector<State> &state, const vector<int> &groups){
    if (groupPos >= groups.size()){
        for (size_t i = pos; i < state.size(); i++){
            if (state[i] == DAMAGED){
                return 0;
            }
        }

        return 1;
    }

    if (pos >= state.size()){
        return 0;
    }

    int64_t res = 0;
    if (state[pos] == OPERATIONAL || state[pos] == UNKNOWN){
        res += combinations(dp, pos + 1, groupPos, state, groups);
    }

    if (pos + groups[groupPos] <= state.size()){
        bool possible = true;
        for (size_t i = pos; i < pos + groups[groupPos]; i++){
            if (state[i] == OPERATIONAL){
                possible = false;
                break;
            }
        }

        if (possible){
            if ((pos + groups[groupPos] < state.size() && state[pos + groups[groupPos]] != DAMAGED) ||
                (pos + groups[groupPos] == state.size())){
                res += combinations(dp, pos + groups[groupPos] + 1, groupPos + 1, state, groups);
            }
        }
    }

    dp[pos][groupPos] = res;
    return res;
}

int64_t combinations(const vector<State> &state, const vector<int> &groups){
    vector<vector<int64_t>> dp(state.size(), vector(groups.size(), (int64_t) -1));

    return combinations(dp, 0, 0, state, groups);
}

int part1(const vector<vector<State>> &states, const vector<vector<int>> &groups){
    int64_t sum = 0;
    for (size_t i = 0; i < states.size(); i++){
        sum += combinations(states[i], groups[i]);
    }
    return sum;
}

int64_t part2(const vector<vector<State>> &states, const vector<vector<int>> &groups){
    int64_t sum = 0;
    for (size_t i = 0; i < states.size(); i++){
        vector<State> unfoldedState;
        vector<int> unfoldedGroup;

        unfoldedState.reserve(5 * states[i].size() + 4);
        unfoldedGroup.reserve(5 * groups[i].size());

        for (size_t j = 0; j < 5; j++){
            unfoldedState.insert(unfoldedState.end(), states[i].begin(), states[i].end());
            unfoldedGroup.insert(unfoldedGroup.end(), groups[i].begin(), groups[i].end());
            if (j != 4){
                unfoldedState.emplace_back(UNKNOWN);
            }
        }

        sum += combinations(unfoldedState, unfoldedGroup);
    }
    return sum;
}

void solve() {
    stringstream input(test);

    string line;
    vector<vector<State>> states;
    vector<vector<int>> groups;

    while(getline(input, line)){
        vector<State> state;
        size_t i;
        for (i = 0; line[i] != ' '; i++){
            if (line[i] == '.'){
                state.emplace_back(OPERATIONAL);
            } else if (line[i] == '#'){
                state.emplace_back(DAMAGED);
            } else if (line[i] == '?'){
                state.emplace_back(UNKNOWN);
            }
        }

        states.emplace_back(state);
        groups.emplace_back(toIntVec(split(line.substr(i), ",")));
    }

    cout << "Part 1: " << part1(states, groups) << endl;
    cout << "Part 2: " << part2(states, groups) << endl;
}
