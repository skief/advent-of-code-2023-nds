#include <nds.h>
#include <gl2d.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "consoleTool.h"

using namespace std;

constexpr char *test =
#include "day02.txt"
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

vector<tuple<int, vector<CubeCount>>> games;
size_t currentGame = 0;
size_t currentSet = 0;
CubeCount minCubes{0, 0, 0};

int part1 = 0;
int part2 = 0;

int part1update = 0;
int part2update = 0;

int repeats = 0;

void vblank() {
    if (currentGame >= games.size()){
        clear();
        setCursorPos(10, 0);
        cout << "        Part 1: " << part1 << endl << endl;
        cout << "        Part 2: " << part2 << endl;

        return;
    }

    auto game = games[currentGame];
    auto set = get<1>(game)[currentSet];

    minCubes.red = max(minCubes.red, set.red);
    minCubes.green = max(minCubes.green, set.green);
    minCubes.blue = max(minCubes.blue, set.blue);

    if (minCubes.red <= 12 && minCubes.green <= 13 && minCubes.blue <= 14){
        part1update = get<0>(game);
    } else {
        part1update = 0;
    }

    part2update = max(minCubes.red * minCubes.green * minCubes.blue, set.red * set.green * set.blue);


    glBegin2D();
    int size = 10;
    int margin = 2;

    int y = 30;
    for (int i = 0; i < set.red; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(31, 0, 0));
    }
    for (int i = set.red; i < minCubes.red; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(5, 0, 0));
    }

    y += 30;
    for (int i = 0; i < set.green; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(0, 31, 0));
    }
    for (int i = set.green; i < minCubes.green; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(0, 3, 0));
    }

    y += 30;
    for (int i = 0; i < set.blue; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(0, 0, 31));
    }
    for (int i = set.blue; i < minCubes.blue; i++){
        int x = i * (size + margin);

        glBoxFilled(x, y, x + size, y + size, RGB15(0, 0, 5));
    }
    glEnd2D();
    glFlush(0);

    clear();
    setCursorPos(5, COLS / 2 - 2);

    setCursorPos(6, 7);
    cout << "Game " << get<0>(game) << " Set " << currentSet << endl;


    setCursorPos(ROWS / 2 - 1, 0);
    cout << "      Min Cubes: " << endl;
    cout << "          Red:   " << minCubes.red << endl;
    cout << "          Green: " << minCubes.green << endl;
    cout << "          Blue:  " << minCubes.blue << endl << endl;
    cout << "          Power: " << minCubes.red * minCubes.green * minCubes.blue << endl;
    cout << "     =====================" << endl;
    cout << "      Part 1: " << part1 << " + " << part1update << endl;
    cout << "      Part 2: " << part2 << " + " << part2update << endl;
    repeats++;

    if (repeats == 10){
        currentSet++;
        if (currentSet >= get<1>(game).size()){
            currentSet = 0;
            currentGame++;
            minCubes.red = 0;
            minCubes.green = 0;
            minCubes.blue = 0;
            part1 = part1 + part1update;
            part2 = part2 + part2update;
        }
        repeats = 0;
    }
}

#define TIMER_SPEED (BUS_CLOCK/1024)
void wait(int seconds){
    timerElapsed(0);

    uint ticks = 0;
    while (ticks / TIMER_SPEED < seconds){
        ticks += timerElapsed(0);
    }
}

int main() {
    stringstream input(test);
    string line;

    while (getline(input, line)){
        games.emplace_back(readGame(line));
    }

    powerOn(POWER_ALL);
    consoleDemoInit();
    videoSetMode(MODE_5_3D);

    glScreen2D();
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankF(VRAM_F_TEX_PALETTE);

    timerStart(0, ClockDivider_1024, 0, NULL);
    wait(2);

    irqSet(IRQ_VBLANK, vblank);

    clear();
    setCursorPos(5, COLS / 2 - 2);

    setCursorPos(ROWS / 2 - 1, 0);

    while(true){
        scanKeys();
        if (keysDown()&KEY_START) break;
    }

    return 0;
}
