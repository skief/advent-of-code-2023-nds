#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>
#include <inttypes.h>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day11.txt"
;

vector<tuple<int64_t, int64_t>> expand(const vector<tuple<int, int>> &galaxies, const vector<int> &emptyRows, const vector<int> &emptyCols, int64_t age){
    vector<tuple<int64_t, int64_t>> result;
    result.reserve(galaxies.size());

    for (const auto &[y, x]: galaxies){
        int64_t newY = y;
        int64_t newX = x;

        for (const auto &row: emptyRows){
            if (row > y){
                break;
            }

            newY += age;
        }

        for (const auto &col: emptyCols){
            if (col > x){
                break;
            }

            newX += age;
        }

        result.emplace_back(newY, newX);
    }

    return result;
}

int64_t shortestPaths(const vector<tuple<int, int>> &galaxies, const vector<int> &emptyRows, const vector<int> &emptyCols, int64_t age){
    auto expanded = expand(galaxies, emptyRows, emptyCols, age);

    int64_t sum = 0;
    for (size_t i = 0; i < expanded.size(); i++){
        auto &[y1, x1] = expanded[i];
        for (size_t j = i + 1; j < expanded.size(); j++){
            auto &[y2, x2] = expanded[j];

            sum += abs(y2 - y1) + abs(x2 - x1);
        }
    }

    return sum;
}

int64_t part1(const vector<tuple<int, int>> &galaxies, const vector<int> &emptyRows, const vector<int> &emptyCols){
    return shortestPaths(galaxies, emptyRows, emptyCols, 1);
}

int64_t part2(const vector<tuple<int, int>> &galaxies, const vector<int> &emptyRows, const vector<int> &emptyCols){
    return shortestPaths(galaxies, emptyRows, emptyCols, 1000000-1);
}


void solve() {
    stringstream input(test);

    string line;

    vector<tuple<int, int>> galaxies;
    vector<int> emptyRows;
    vector<int> emptyCols;

    vector<bool> colState;

    int y = 0;
    while (getline(input, line)) {
        if (colState.empty()) {
            colState.reserve(line.size());
            for (int i = 0; i < line.size(); i++) {
                colState.emplace_back(true);
            }
        }

        bool emptyRow = true;
        for (int x = 0; x < line.size(); x++) {
            if (line[x] == '#') {
                emptyRow = false;
                colState[x] = false;
                galaxies.emplace_back(y, x);
            }
        }

        if (emptyRow) {
            emptyRows.emplace_back(y);
        }
        y++;
    }

    for (int x = 0; x < colState.size(); x++) {
        if (colState[x]) {
            emptyCols.emplace_back(x);
        }
    }

    cout << "Part 1: " << part1(galaxies, emptyRows, emptyCols) << endl;
    cout << "Part 2: " << part2(galaxies, emptyRows, emptyCols) << endl;
}
