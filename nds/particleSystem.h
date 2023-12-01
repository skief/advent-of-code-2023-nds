#pragma once

#define NUM_PARTICLES 800

class ParticleSystem {
private:
    int x[NUM_PARTICLES];
    int y[NUM_PARTICLES];

    int y_speed[NUM_PARTICLES];

    void spawn(size_t i);

public:
    ParticleSystem();
    void update(int wind);
    void render();
};
