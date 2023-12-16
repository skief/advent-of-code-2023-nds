#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

constexpr char *test = (char*)
#include "../../inputs/day16.txt"
;

enum Direction{
    UP, RIGHT, DOWN, LEFT
};

const Direction mirror1[] = {RIGHT, UP, LEFT, DOWN};
const Direction mirror2[] = {LEFT, DOWN, RIGHT, UP};

void beam(const vector<string> &cave, int startY, int startX, Direction startDir, vector<vector<vector<bool>>> &visited){
    queue<tuple<int, int, Direction>> todo;
    todo.emplace(startY, startX, startDir);

    while (!todo.empty()){
        auto [y, x, dir] = todo.front();
        todo.pop();

        auto &vis = visited[dir];

        int dx = 0;
        int dy = 0;

        if (dir == UP){
            dy = -1;
        } else if (dir == DOWN){
            dy = 1;
        } else if (dir == LEFT){
            dx = -1;
        } else if (dir == RIGHT){
            dx = 1;
        }

        while (y + dy >= 0 && y + dy < vis.size() && x + dx >= 0 && x + dx < vis[0].size()){
            y = y + dy;
            x = x + dx;
            if (vis[y][x]){
                break;
            }
            vis[y][x] = true;

            if (cave[y][x] == '/'){
                todo.emplace(y, x, mirror1[dir]);
                break;
            } else if (cave[y][x] == '\\'){
                todo.emplace(y, x, mirror2[dir]);
                break;
            } else if (cave[y][x] == '-' && dx == 0){
                todo.emplace(y, x, LEFT);
                todo.emplace(y, x, RIGHT);
                break;
            } else if (cave[y][x] == '|' && dy == 0){
                todo.emplace(y, x, UP);
                todo.emplace(y, x, DOWN);
                break;
            }
        }
    }

}

int countEnergized(const vector<string> &cave, int y, int x, Direction dir){
    vector<vector<vector<bool>>> visited(4, vector(cave.size(), vector(cave[0].size(), false)));

    beam(cave, y, x, dir, visited);

    int sum = 0;
    for (int y = 0; y < cave.size(); y++){
        for (int x = 0; x < cave[y].size(); x++){
            if (visited[UP][y][x] || visited[RIGHT][y][x] || visited[DOWN][y][x] || visited[LEFT][y][x]) {
                sum++;
            }
        }
    }

    return sum;
}

int part1(const vector<string> &cave){
    return countEnergized(cave, 0, -1, RIGHT);
}

int part2(const vector<string> &cave){
    int best = 0;

    for (int x = 0; x < cave[0].size(); x++){
        int t = countEnergized(cave, -1, x, DOWN);
        if (t > best){
            best = t;
        }

        t = countEnergized(cave, cave.size(), x, UP);
        if (t > best){
            best = t;
        }
    }

    for (int y = 0; y < cave.size(); y++){
        int t = countEnergized(cave, y, -1, RIGHT);
        if (t > best){
            best = t;
        }

        t = countEnergized(cave, y, cave[0].size(), LEFT);
        if (t > best){
            best = t;
        }
    }

    return best;
}

void solve() {
    stringstream input(test);

    string line;
    vector<string> cave;
    while(getline(input, line)){
        cave.emplace_back(line);
    }

    cout << "Part 1: " << part1(cave) << endl;
    cout << "Part 2: " << part2(cave) << endl;
}
