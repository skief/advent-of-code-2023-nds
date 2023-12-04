#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day04.txt"
;


void solve(){
    stringstream input(test);

    string line;

    vector<tuple<vector<int>, vector<int>>> cards;
    while (getline(input, line)){
        line = line.substr(line.find(": ") + 2);

        size_t sep = line.find(" | ");
        vector<int> numbers = toIntVec(split(line.substr(0, sep), " "));
        vector<int> winning = toIntVec(split(line.substr(sep + 3), " "));

        cards.emplace_back(numbers, winning);
    }

    int part1 = 0;
    int part2 = 0;
    vector<int> copies(cards.size(), 1);

    for (size_t i = 0; i < cards.size(); i++){
        auto card = cards[i];
        int hits = 0;
        int points = 0;
        auto winning = get<1>(card);
        for (auto number: get<0>(card)){
            if (find(winning.begin(), winning.end(), number) != winning.end()){
                hits++;

                if (points == 0){
                    points = 1;
                } else {
                    points *= 2;
                }
            }
        }

        for (size_t j = 1; j <= hits; j++){
            copies[i + j] += copies[i];
        }

        part1 += points;
        part2 += copies[i];
    }



    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}
