#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

constexpr char *test =
#include "../../inputs/day02.txt"
;

typedef struct {
    int red;
    int green;
    int blue;
} CubeCount;

vector<string> split(const string& txt, const string& delim){
    vector<string> results;

    size_t start = 0;
    size_t end;

    while ((end = txt.find(delim, start)) != string::npos){
        results.emplace_back(txt.substr(start, end - start));
        start = end + delim.size();
    }

    results.emplace_back(txt.substr(start));

    return results;
}

tuple<int, vector<CubeCount>> readGame(const string& line){
    size_t start, end;

    start = line.find("Game ");
    end = line.find(':', start + 5);

    int id = stoi(line.substr(start + 5, end));

    vector<CubeCount> sets;

    for (auto& set: split(line.substr(end + 2), "; ")){
        vector<string> draws = split(set, ", ");
        CubeCount cubes = {0, 0, 0};
        for (auto& draw: draws){
            vector<string> temp = split(draw, " ");
            string color = temp[1];
            int count = stoi(temp[0]);

            if (color == "red"){
                cubes.red = count;
            } else if (color == "blue"){
                cubes.blue = count;
            } else if (color == "green") {
                cubes.green = count;
            } else {
                cout << "oops" << color << "a" << endl;
            }
        }

        sets.emplace_back(cubes);
    }

    return {id, sets};
}

CubeCount minRequiredCubes(const vector<CubeCount> &sets){
    CubeCount minCubes = {0, 0, 0};

    for (auto &set: sets){
        if (set.red > minCubes.red){
            minCubes.red = set.red;
        }
        if (set.green > minCubes.green){
            minCubes.green = set.green;
        }
        if (set.blue > minCubes.blue){
            minCubes.blue = set.blue;
        }
    }

    return minCubes;
}

void solve(){
    stringstream input(test);

    string line;

    vector<tuple<int, vector<CubeCount>>> games;
    while (getline(input, line)){
        games.emplace_back(readGame(line));
    }

    int part1 = 0;
    for (auto &game: games){
        CubeCount requiredCubes = minRequiredCubes(get<1>(game));
        if (requiredCubes.red <= 12 && requiredCubes.green <= 13 && requiredCubes.blue <= 14){
            part1 += get<0>(game);
        }
    }

    int part2 = 0;
    for (auto &game: games){
        CubeCount requiredCubes = minRequiredCubes(get<1>(game));
        part2 += requiredCubes.red * requiredCubes.green * requiredCubes.blue;
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}
