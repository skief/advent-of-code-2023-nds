#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day14.txt"
;

struct pos2d{
    int y;
    int x;
};

vector<vector<int>> north(const vector<vector<int>> &roundCol, const vector<vector<int>> &cubeCols, int height, int width){
    vector<vector<int>> resRow(height, vector<int>());

    for (int x = 0; x < width; x++){
        if (cubeCols[x].empty()){
            int count = roundCol[x].size();

            for (int i = 0; i < count; i++){
                resRow[i].emplace_back(x);
            }
        } else {
            int lower = -1;
            int upper;
            for (int i = 0; i < cubeCols[x].size(); i++){
                upper = cubeCols[x][i];

                int count = 0;
                for (const auto &r: roundCol[x]){
                    if (r > lower && r < upper){
                        count++;
                    }
                }

                for (int i = 0; i < count; i++){
                    resRow[lower + i + 1].emplace_back(x);
                }

                lower = upper;
            }

            int count = 0;
            for (const auto &r: roundCol[x]){
                if (r > lower){
                    count++;
                }
            }

            for (int i = 0; i < count; i++){
                resRow[lower + i + 1].emplace_back(x);
            }
        }
    }

    return resRow;
}

vector<vector<int>> south(const vector<vector<int>> &roundCol, const vector<vector<int>> &cubeCols, int height, int width){
    vector<vector<int>> resRow(height, vector<int>());

    for (int x = 0; x < width; x++){
        if (cubeCols[x].empty()){
            int count = roundCol[x].size();

            for (int i = 0; i < count; i++){
                resRow[height - i - 1].emplace_back(x);
            }
        } else {
            int lower = 0;
            int upper = height;
            for (int i = 0; i < cubeCols[x].size(); i++){
                lower = cubeCols[x][cubeCols[x].size() - i - 1];

                int count = 0;
                for (const auto &r: roundCol[x]){
                    if (r > lower && r < upper){
                        count++;
                    }
                }

                for (int i = 0; i < count; i++){
                    resRow[upper - i - 1].emplace_back(x);
                }

                upper = lower;
            }

            int count = 0;
            for (const auto &r: roundCol[x]){
                if (r < lower){
                    count++;
                }
            }

            for (int i = 0; i < count; i++){
                resRow[upper - i - 1].emplace_back(x);
            }
        }
    }

    return resRow;
}

int part1(const vector<pos2d> &round, const vector<pos2d> &cube, int height, int width){
    vector<vector<int>> cubeCols(width, vector<int>());
    for (const auto &c: cube){
        cubeCols[c.x].emplace_back(c.y);
    }

    vector<vector<int>> roundCols(width, vector<int>());
    for (const auto &r: round){
        roundCols[r.x].emplace_back(r.y);
    }

    auto roundRows = north(roundCols, cubeCols, height, width);

    int weight = 0;
    for (int y = 0; y < height; y++){
        weight += roundRows[y].size() * (height - y);
    }

    return weight;
}

int part2(const vector<pos2d> &round, const vector<pos2d> &cube, int height, int width){
    vector<vector<int>> cubeCols(width, vector<int>());
    for (const auto &c: cube){
        cubeCols[c.x].emplace_back(c.y);
    }

    vector<vector<int>> cubeRows(height, vector<int>());
    for (const auto &c: cube){
        cubeRows[c.y].emplace_back(c.x);
    }

    vector<vector<int>> roundCols(width, vector<int>());
    for (const auto &r: round){
        roundCols[r.x].emplace_back(r.y);
    }

    map<vector<vector<int>>, int> encountered;

    vector<vector<int>> roundRows;

    const int numRounds = 1000000000;
    for (int i = 0; i < numRounds; i++){
        roundRows = north(roundCols, cubeCols, height, width);
        roundCols = north(roundRows, cubeRows, width, height);
        roundRows = south(roundCols, cubeCols, height, width);
        roundCols = south(roundRows, cubeRows, width, height);

        if (encountered.contains(roundRows)){
            int dist = i - encountered[roundRows];
            i = i + ((numRounds - i) / dist) * dist;
        }
        encountered[roundRows] = i;
    }

    int weight = 0;
    for (int y = 0; y < height; y++){
        weight += roundRows[y].size() * (height - y);
    }

    return weight;
}

void solve() {
    stringstream input(test);

    string line;
    vector<pos2d> roundRocks;
    vector<pos2d> cubeRocks;

    int y = 0;
    while(getline(input, line)){
        for (int x = 0; x < line.size(); x++){
            if (line[x] == 'O'){
                roundRocks.emplace_back(y, x);
            } else if (line[x] == '#'){
                cubeRocks.emplace_back(y, x);
            }
        }

        y++;
    }

    cout << "Part 1: " << part1(roundRocks, cubeRocks, y, line.size()) << endl;
    cout << "Part 2: " << part2(roundRocks, cubeRocks, y, line.size()) << endl;
}
