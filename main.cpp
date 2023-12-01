#include <nds.h>
#include <fat.h>

#include <iostream>

#include "nds/graphics.h"
#include "nds/sounds.h"
#include "nds/consoleTool.h"

#include "solution.h"

#ifndef DAY
#error "DAY not defined"
#endif

#define TIMER_SPEED (BUS_CLOCK/1024)

using namespace std;

Graphics graphics;

int day = DAY - 1;

void vblank() {
    graphics.update(day);
}

void wait(int seconds){
    timerElapsed(0);

    uint ticks = 0;
    while (ticks / TIMER_SPEED < seconds){
        ticks += timerElapsed(0);
    }
}

int main() {
    powerOn(POWER_ALL);
    consoleDemoInit();

    timerStart(0, ClockDivider_1024, 0, NULL);
    Sounds::init();
    Sounds::start();

    // wait(3);

    fatInitDefault();

    graphics.init();

    irqSet(IRQ_VBLANK, vblank);

    clear();
    setCursorPos(5, COLS / 2 - 2);
    cout << "Day " << DAY  << endl;

    setCursorPos(ROWS / 2 - 1, 0);
    solve();

    day++;

    while(true){
        scanKeys();
        if (keysDown()&KEY_START) break;
    }

    return 0;
}
