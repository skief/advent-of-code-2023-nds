#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day03.txt"
;

const int neighbors[][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                            {1,  -1}, {1, 0}, {1, 1},
                            {0,  -1}, {0, 1}};


bool isNumber(char x){
    return (x >= '0' && x <= '9');
}

int part1(const vector<string> &engine){
    int sum = 0;

    for (size_t row = 0; row < engine.size(); row++){
        int numStart = -1;
        bool found = false;

        for (size_t col = 0; col < engine[row].size(); col++){
            if (isNumber(engine[row][col])){
                if (numStart == -1){
                    numStart = col;
                }

                if (!found){
                    for (auto neigh: neighbors){
                        int y = row + neigh[0];
                        int x = col + neigh[1];

                        if (x < 0 || x >= engine[row].size() || y < 0 || y >= engine.size()){
                            continue;
                        }

                        if (engine[y][x] != '.' && !isNumber(engine[y][x])){
                            found = true;
                            break;
                        }
                    }
                }
            } else if (numStart != -1){
                if (found){
                    sum += stoi(engine[row].substr(numStart, col - numStart));
                }

                found = false;
                numStart = -1;
            }
        }

        if (numStart != -1){
            if (found){
                sum += stoi(engine[row].substr(numStart));
            }
        }
    }

    return sum;
}

int part2(const vector<string> &engine){
    int sum = 0;

    for (size_t row = 0; row < engine.size(); row++){
        for (size_t col = 0; col < engine[row].size(); col++){
            if (engine[row][col] != '*'){
                continue;
            }

            vector<int> numbers;
            vector<tuple<size_t, size_t>> numberPos;

            for (auto neigh: neighbors){
                int y = row + neigh[0];
                int x = col + neigh[1];

                if (x < 0 || x >= engine[row].size() || y < 0 || y >= engine.size()){
                    continue;
                }

                if (isNumber(engine[y][x])){
                    while (x >= 0 && isNumber(engine[y][x])){
                        x--;
                    }
                    if (x < 0 || !isNumber(engine[y][x])) {
                        x++;
                    }

                    tuple<size_t, size_t> pos(y, x);

                    if (find(numberPos.begin(), numberPos.end(), pos) == numberPos.end()){
                        numberPos.emplace_back(pos);

                        size_t start = x;
                        while (x < engine[y].size() && isNumber(engine[y][x])){
                            x++;
                        }
                        if (x == engine[y].size() || !isNumber(engine[y][x])) {
                            x--;
                        }

                        numbers.emplace_back(stoi(engine[y].substr(start, x - start + 1)));
                    }
                }
            }

            if (numbers.size() == 2){
                sum += numbers[0] * numbers[1];
            }
        }
    }

    return sum;
}

void solve(){
    stringstream input(test);

    string line;

    vector<string> engine;
    while (getline(input, line)){
        engine.emplace_back(line);
    }

    cout << "Part 1: " << part1(engine) << endl;
    cout << "Part 2: " << part2(engine) << endl;
}
