#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <algorithm>

#include "utils.h"

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day05.txt"
;

class Range{
public:
    int64_t start;
    int64_t range;

    Range(int64_t start, int64_t range): start(start), range(range){}

    bool contains(int64_t val) const {
        return val >= start && val < start + range;
    }

    bool overlaps(const Range &other) const {
        return max(start, other.start) < min(start + range, other.start + other.range);
    }
};

class Translator {
public:
    vector<Range> source;
    vector<int64_t> offset;

    void add(int64_t src, int64_t dst, int64_t r) {
        source.emplace_back(src, r);
        offset.emplace_back(dst - src);
    }

    int64_t get(int64_t val) const {
        for (size_t i = 0; i < source.size(); i++) {
            if (source[i].contains(val)) {
                return offset[i] + val;
            }
        }

        return val;
    }

    vector<Range> get(Range val) const {
        vector<Range> result;

        bool hit = false;

        int64_t valStart = val.start;
        int64_t valEnd = val.start + val.range;

        for (size_t i = 0; i < source.size(); i++) {
            if (!source[i].overlaps(val)) {
                continue;
            }

            hit = true;

            int64_t start = source[i].start;
            int64_t end = source[i].start + source[i].range;

            if (start <= valStart && valEnd <= end) {
                result.emplace_back(offset[i] + valStart, val.range);

            } else if (start <= valStart && end <= valEnd) {
                int64_t range = end - valStart;
                result.emplace_back(offset[i] + valStart, range);

                auto next = get(Range{end, valEnd - end});
                result.insert(result.end(), next.begin(), next.end());

            } else if (valStart <= start && valEnd <= end) {
                int64_t range = valEnd - start;
                result.emplace_back(offset[i] + start, range);

                auto next = get(Range{valStart, start - valStart});
                result.insert(result.end(), next.begin(), next.end());

            } else if (valStart <= start && end <= valEnd) {
                result.emplace_back(start, source[i].range);

                auto next = get(Range{valStart, start - valStart});
                result.insert(result.end(), next.begin(), next.end());

                next = get(Range{end, valEnd - end});
                result.insert(result.end(), next.begin(), next.end());

            } else {
                cout << "?" << endl;
            }
        }

        if (!hit) {
            result.emplace_back(val);
        }

        return result;
    }
};

Translator read(stringstream &input){
    Translator result;

    string line;
    while (getline(input, line)){
        if (line.empty()){
            return result;
        }

        auto values = toIntVec64(split(line, " "));
        int64_t dstStart = values[0];
        int64_t srcStart = values[1];
        int64_t range = values[2];

        result.add(srcStart, dstStart, range);
    }

    return result;
}

int64_t part1(const map<tuple<string, string>, Translator> &maps, const map<string, string> &fromToPairs,
              const vector<int64_t> &seeds){
    vector<int64_t> values(seeds);

    string from = "seed";
    while (from != "location"){
        string to = fromToPairs.at(from);

        const Translator &trans = maps.at(tuple{from, to});

        for (auto &val: values){
            val = trans.get(val);
        }

        from = to;
    }

    return *std::min_element(begin(values), end(values));
}

int64_t mapAll(const map<tuple<string, string>, Translator> &maps, const map<string, string> &fromToPairs,
               const Range value, string from){
    if (from == "location"){
        return value.start;
    }

    string to = fromToPairs.at(from);
    const Translator &trans = maps.at(tuple{from, to});
    auto next = trans.get(value);

    int64_t min = -1;
    for (size_t i = 0; i < next.size(); i++){
        int64_t val = mapAll(maps, fromToPairs, next[i], to);

        if (i == 0 || val < min){
            min = val;
        }
    }

    return min;
}

int64_t part2(const map<tuple<string, string>, Translator> &maps, const map<string, string> &fromToPairs,
               const vector<int64_t> &seeds) {
    int64_t min = -1;
    for (size_t i = 0; i < seeds.size() / 2; i++) {
        int64_t val = mapAll(maps, fromToPairs, Range{seeds[2 * i], seeds[2 * i + 1]}, "seed");
        if (i == 0 || val < min) {
            min = val;
        }
    }

    return min;
}


void solve(){
    stringstream input(test);

    map<tuple<string, string>, Translator> maps;
    map<string, string> fromToPairs;

    string line;

    getline(input, line);
    vector<int64_t> seeds = toIntVec64(split(line.substr(line.find(": ") + 2), " "));

    while(getline(input, line)){
        size_t sepPos = line.find('-');
        if (sepPos == string::npos){
            continue;
        }

        string from = line.substr(0, sepPos);
        sepPos = line.find('-', sepPos + 1);

        string to = line.substr(sepPos + 1, line.find(' ', sepPos + 1) - sepPos - 1);

        fromToPairs[from] = to;

        maps[{from, to}] = read(input);
    }

    cout << "Part 1: " << part1(maps, fromToPairs, seeds) << endl;
    cout << "Part 2: " << part2(maps, fromToPairs, seeds) << endl;
}
