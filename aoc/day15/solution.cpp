#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day15.txt"
;

int hashString(const string &txt){
    int value = 0;

    for (const auto &c: txt){
        value += c;
        value *= 17;
        value %= 256;
    }

    return value;
}

int part1(const vector<string> &strings){
    int sum = 0;

    for (const string &s: strings){
        sum += hashString(s);
    }

    return sum;
}

struct KeyVal {
    string key;
    int value;
};

int part2(const vector<string> &strings){
    map<int, vector<KeyVal>> hashmap;

    for (const string &s: strings){
        size_t pos = s.find('=');
        if (pos != string::npos){
            string key = s.substr(0, pos);
            int val = stoi(s.substr(pos + 1));
            int keyHash = hashString(key);
            bool found = false;

            for (auto &kv: hashmap[keyHash]){
                if (kv.key == key){
                    kv.value = val;
                    found = true;
                    break;
                }
            }

            if (!found){
                hashmap[keyHash].emplace_back(key, val);
            }

        } else if (s[s.size() - 1] == '-'){
            string key = s.substr(0, s.size() - 1);
            int keyHash = hashString(key);

            for (auto it = hashmap[keyHash].begin(); it != hashmap[keyHash].end(); it++){
                if (it->key == key){
                    hashmap[keyHash].erase(it);
                    break;
                }
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < 256; i++){
        for (int j = 0; j < hashmap[i].size(); j++){
            const KeyVal &kv = hashmap[i][j];
            sum += (i + 1) * (j + 1) * kv.value;
        }
    }


    return sum;
}

void solve() {
    stringstream input(test);

    string line;
    getline(input, line);
    vector<string> strings = split(line, ",");

    cout << "Part 1: " << part1(strings) << endl;
    cout << "Part 2: " << part2(strings) << endl;
}
