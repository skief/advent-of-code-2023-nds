#pragma once

#include <iostream>
#include <string>

const int ROWS = 24;
const int COLS = 32;

void clear(){
    std::cout << "\x1b[2J";
}

void setCursorPos(int row, int col){
    std::cout << "\x1b[" + std::to_string(row) + ";" + std::to_string(col) + "H";
}

