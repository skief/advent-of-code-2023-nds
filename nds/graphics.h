#pragma once
#include <nds.h>
#include <gl2d.h>

#include "christmasTree.h"
#include "particleSystem.h"

class Graphics {
private:
    ChristmasTree tree;
    ParticleSystem snow;
    glImage background[1];

public:
    void init();
    void update(int day);
};

