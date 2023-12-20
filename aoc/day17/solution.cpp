#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day17.txt"
;

enum Direction {
    NORTH = 0, EAST, SOUTH, WEST
};

const int dY[] = {-1, 0, 1, 0};
const int dX[] = {0, 1, 0, -1};

struct State {
    int16_t y;
    int16_t x;

    int8_t lastDir;

    bool operator < (const State &other) const {
        if (y < other.y){
            return true;
        } else if (y > other.y){
            return false;
        }

        if (x < other.x){
            return true;
        } else if (x > other.x){
            return false;
        }

        if (lastDir < other.lastDir){
            return true;
        }

        return false;
    }
};

struct StateCost {
    State state;
    int16_t cost;

    bool operator > (const StateCost &other) const{
        return cost > other.cost;
    }
};

vector<StateCost> nextStates(const vector<vector<int8_t>> &heatLoss, const State &state, int minSteps, int maxSteps, int h, int w){
    vector<StateCost> next;

    for (int8_t i = -1; i < 2; i++){
        if (i == 0){
            continue;
        }

        int8_t newDir = (state.lastDir + 4 + i) % 4;

        int16_t cost = 0;

        int16_t nextY = state.y;
        int16_t nextX = state.x;

        for (int s = 0; s < maxSteps; s++){
            nextY += dY[newDir];
            nextX += dX[newDir];

            if (nextY < 0 || nextY >= h || nextX < 0 || nextX >= w){
                break;
            }

            cost += heatLoss[nextY][nextX];

            if (s < minSteps){
                continue;
            }

            next.emplace_back(State{nextY, nextX, newDir}, cost);
        }
    }

    return next;
}

int shortestPath(const vector<vector<int8_t>> &heatLoss, int minSteps, int maxSteps){
    priority_queue<StateCost, vector<StateCost>, greater<>> nextVisits;

    const int h = heatLoss.size();
    const int w = heatLoss[0].size();

    map<State, int16_t> costs;

    State init{0, 0, NORTH};
    costs[init] = 0;
    State init2{0, 0, WEST};
    costs[init2] = 0;
    nextVisits.push({init, 0});
    nextVisits.push({init2, 0});

    while (!nextVisits.empty()){
        StateCost curr = nextVisits.top();
        nextVisits.pop();

        if (curr.state.y == h - 1 && curr.state.x == w - 1){
            return curr.cost;
        }

        if (costs.contains(curr.state) && costs.at(curr.state) < curr.cost){
            continue;
        }

        for (auto next: nextStates(heatLoss, curr.state, minSteps, maxSteps, h, w)){
            int16_t nextCost = curr.cost + next.cost;

            if (!costs.contains(next.state) || nextCost < costs.at(next.state)){
                costs[next.state] = nextCost;
                nextVisits.push({next.state, nextCost});
            }
        }
    }

    return -1;
}

int part1(const vector<vector<int8_t>> &heatLoss){
    return shortestPath(heatLoss, 0, 3);
}

int part2(const vector<vector<int8_t>> &heatLoss){
    return shortestPath(heatLoss, 3, 10);
}

void solve() {
    stringstream input(test);

    string line;
    vector<vector<int8_t>> heatLoss;
    while(getline(input, line)){
        vector<int8_t> loss;
        for (const auto &c: line){
            loss.emplace_back(c - '0');
        }
        heatLoss.emplace_back(loss);
    }

    cout << "Part 1: " << part1(heatLoss) << endl;
    cout << "Part 2: " << part2(heatLoss) << endl;
}
