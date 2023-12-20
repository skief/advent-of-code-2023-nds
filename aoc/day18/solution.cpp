#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day18.txt"
;

enum Direction {RIGHT, DOWN, LEFT, UP};
const int directionsY[] = {0, 1, 0, -1};
const int directionsX[] = {1, 0, -1, 0};

tuple<vector<tuple<int64_t, int64_t>>, int64_t> buildPolygon(const vector<tuple<Direction, int>> &digPlan){
    vector<tuple<int64_t , int64_t>> polygon;
    polygon.reserve(digPlan.size());
    int64_t edgeLen = 0;

    int64_t y = 0;
    int64_t x = 0;

    for (const auto &[dir, len]: digPlan){
        y += len * directionsY[dir];
        x += len * directionsX[dir];
        edgeLen += len;

        polygon.emplace_back(y, x);
    }

    return {polygon, edgeLen};
}

int64_t area(const vector<tuple<int64_t, int64_t>> polygon, int64_t edgeLen){
    int64_t shoelace = 0;
    for (size_t i = 0; i < polygon.size(); i++){
        size_t next = (i + 1) % polygon.size();

        shoelace += get<1>(polygon[i]) * get<0>(polygon[next]) - get<0>(polygon[i]) * get<1>(polygon[next]);
    }
    shoelace = shoelace / 2;

    int64_t inner = shoelace - edgeLen / 2 + 1;

    return edgeLen + inner;
}

int64_t part1(const vector<tuple<Direction, int>> &digPlan){
    auto [polygon, edgeLen] = buildPolygon(digPlan);

    return area(polygon, edgeLen);
}

int64_t part2(const vector<string> &colors){
    vector<tuple<Direction, int>> digPlan;
    digPlan.reserve(colors.size());

    for (const auto &c: colors){
        int len = strtol(c.substr(0, 5).c_str(), nullptr, 16);
        Direction dir = static_cast<Direction>(strtol(c.substr(5).c_str(), nullptr, 16));

        digPlan.emplace_back(dir, len);
    }

    auto [polygon, edgeLen] = buildPolygon(digPlan);

    return area(polygon, edgeLen);
}

void solve(){
    stringstream input(test);

    vector<tuple<Direction, int>> digPlan;
    vector<string> colors;

    string line;
    while(getline(input, line)){
        Direction dir;
        switch (line[0]) {
            case 'U': dir = UP; break;
            case 'D': dir = DOWN; break;
            case 'L': dir = LEFT; break;
            case 'R': dir = RIGHT; break;
        }

        size_t pos = line.find(' ', 2);
        int len = stoi(line.substr(2, pos - 2));

        string hex = line.substr(pos + 3, line.find(')') - pos - 3);

        digPlan.emplace_back(dir, len);
        colors.emplace_back(hex);
    }

    cout << "Part 1: " << part1(digPlan) << endl;
    cout << "Part 2: " << part2(colors) << endl;
}
