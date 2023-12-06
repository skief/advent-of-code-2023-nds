#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day06.txt"
;

int64_t solve(int64_t time, int64_t dist){
    double t_2 = time / 2.0;
    double root = sqrt(t_2 * t_2 - dist - 1);

    int64_t lower = ceil(t_2 - root);
    int64_t upper = floor(t_2 + root);

    return upper - lower + 1;
}

int64_t part1(const vector<int> &times, const vector<int> &distances){
    int64_t res = 1;

    for (size_t i = 0; i < times.size(); i++){
        res *= solve(times[i], distances[i]);
    }

    return res;
}

int64_t part2(int64_t time, int64_t distance){
    return solve(time, distance);
}

void solve(){
    stringstream input(test);

    string line;
    getline(input, line);
    vector<int> times = toIntVec(split(line.substr(line.find(": ") + 2), " "));
    getline(input, line);
    vector<int> distances = toIntVec(split(line.substr(line.find(": ") + 2), " "));

    string timeStr;
    string distStr;
    for (size_t i = 0; i < times.size();i ++){
        timeStr += to_string(times[i]);
        distStr += to_string(distances[i]);
    }

    cout << "Part 1: " << part1(times, distances) << endl;
    cout << "Part 2: " << part2(stoll(timeStr), stoll(distStr)) << endl;
}
