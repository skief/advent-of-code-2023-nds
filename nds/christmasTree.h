#pragma once

class ChristmasTree {
private:
    glImage textures_32[128 / 16];

    constexpr static const int star[2] = {115, 29};

public:
    void init();
    void render(int day);
};
