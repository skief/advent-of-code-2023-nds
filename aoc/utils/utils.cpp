#include "utils.h"

using namespace std;

vector<string> split(const string& txt, const string& delim){
    vector<string> results;

    size_t start = 0;
    size_t end;

    while ((end = txt.find(delim, start)) != string::npos){
        if (end - start > 0){
            results.emplace_back(txt.substr(start, end - start));
        }
        start = end + delim.size();
    }

    if (!txt.substr(start).empty()){
        results.emplace_back(txt.substr(start));
    }

    return results;
}

vector<int> toIntVec(const vector<string>& strVec){
    vector<int> results;

    results.reserve(strVec.size());
    for (const auto& str: strVec){
        results.emplace_back(stoi(str));
    }

    return results;
}
