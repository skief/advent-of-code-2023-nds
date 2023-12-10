#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day10.txt"
;


enum Direction {
    N, E, S, W, None
};

const map<char, tuple<Direction, Direction>> pipes = {
        {'|', {N, S}},
        {'-', {E, W}},
        {'L', {N, E}},
        {'J', {N, W}},
        {'7', {S, W}},
        {'F', {S, E}},
        {'.', {None, None}}
};

vector<vector<int>> visit(const vector<vector<tuple<Direction, Direction>>> &pipeMap, int startY, int startX){
    vector<vector<int>> visited;
    visited.reserve(pipeMap.size());
    for (size_t y = 0; y < pipeMap.size(); y++){
        visited.emplace_back(pipeMap[y].size(), -1);
    }

    set<tuple<int, int>> check = {{startY, startX}};
    int depth = 0;
    while (!check.empty()){
        set<tuple<int, int>> next;

        for (const auto &[y, x]: check){
            if (visited[y][x] != -1){
                continue;
            }
            visited[y][x] = depth;
            auto dirs = pipeMap[y][x];

            switch (get<0>(dirs)) {
                case N:
                    next.emplace(y - 1, x);
                    break;
                case S:
                    next.emplace(y + 1, x);
                    break;
                case E:
                    next.emplace(y, x + 1);
                    break;
                case W:
                    next.emplace(y, x - 1);
                    break;
            }

            switch (get<1>(dirs)) {
                case N:
                    next.emplace(y - 1, x);
                    break;
                case S:
                    next.emplace(y + 1, x);
                    break;
                case E:
                    next.emplace(y, x + 1);
                    break;
                case W:
                    next.emplace(y, x - 1);
                    break;
            }
        }

        check = next;
        depth++;
    }

    return visited;
}

int part1(const vector<vector<int>> visited){
    int deepest = 0;
    for (auto &row: visited){
        for (auto &col: row){
            if (col > deepest){
                deepest = col;
            }
        }
    }

    return deepest;
}

int part2(const vector<vector<tuple<Direction, Direction>>> &pipeMap, const vector<vector<int>> visited){
    vector<vector<bool>> area;
    area.reserve(pipeMap.size());
    for (size_t y = 0; y < pipeMap.size(); y++){
        area.emplace_back(pipeMap[y].size(), false);
    }

    for (size_t row = 0; row < pipeMap.size(); row++){
        bool inside = false;
        tuple<Direction, Direction> lastCorner = {None, None};

        for (size_t col = 0; col < pipeMap[row].size(); col++){
            if (visited[row][col] == -1) {
                area[row][col] = inside;
            } else {
                auto tile = pipeMap[row][col];

                if (tile == pipes.at('|')){
                    inside = !inside;
                } else if (tile == pipes.at('L') || tile == pipes.at('F')){
                    lastCorner = tile;
                } else if (tile == pipes.at('J') && lastCorner == pipes.at('F')){
                    inside = !inside;
                } else if (tile == pipes.at('7') && lastCorner == pipes.at('L')){
                    inside = !inside;
                }
            }
        }
    }

    int count = 0;
    for (size_t row = 0; row < pipeMap.size(); row++) {
        for (size_t col = 0; col < pipeMap[row].size(); col++) {
            if (area[row][col]) {
                count++;
            }
        }
    }

    return count;
}


void solve(){
    stringstream input(test);

    string line;
    vector<vector<tuple<Direction, Direction>>> pipeMap;

    int y = 0;
    int startX = 0;
    int startY = 0;

    while(getline(input, line)){
        pipeMap.emplace_back();

        for (int x = 0; x < line.size(); x++){
            if (line[x] == 'S'){
                startX = x;
                startY = y;

                pipeMap[pipeMap.size() - 1].emplace_back(pipes.at('.'));
            } else {
                pipeMap[pipeMap.size() - 1].emplace_back(pipes.at(line[x]));
            }
        }
        y++;
    }

    vector<Direction> startConnections;
    startConnections.reserve(2);

    if (startY - 1 >= 0 && (get<0>(pipeMap[startY - 1][startX]) == S || get<1>(pipeMap[startY - 1][startX]) == S)){
        startConnections.emplace_back(N);
    }
    if (startY + 1 < pipeMap.size() && (get<0>(pipeMap[startY + 1][startX]) == N || get<1>(pipeMap[startY + 1][startX]) == N)){
        startConnections.emplace_back(S);
    }
    if (startX + 1 < pipeMap[startY].size() && (get<0>(pipeMap[startY][startX + 1]) == W || get<1>(pipeMap[startY][startX + 1]) == W)){
        startConnections.emplace_back(E);
    }
    if (startX - 1 >= 0 && (get<0>(pipeMap[startY][startX - 1]) == E || get<1>(pipeMap[startY][startX - 1]) == E)){
        startConnections.emplace_back(W);
    }

    pipeMap[startY][startX] = {startConnections[0], startConnections[1]};

    vector<vector<int>> visited = visit(pipeMap, startY, startX);

    cout << "Part 1: " << part1(visited) << endl;
    cout << "Part 2: " << part2(pipeMap, visited) << endl;
}
