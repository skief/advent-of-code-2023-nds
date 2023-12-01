#include <gl2d.h>
#include <cstdlib>

#include "particleSystem.h"

#define MAX_X 255
#define MAX_Y 191


ParticleSystem::ParticleSystem(){
    for (size_t i = 0; i < NUM_PARTICLES; i++){
        spawn(i);
        y[i] = rand() % (MAX_Y + 1);
    }
}

void ParticleSystem::spawn(size_t i){
    x[i] = rand() % (MAX_X + 1);
    y[i] = 0;

    y_speed[i] = rand() % 3 + 1;
}

void ParticleSystem::update(int wind){
    for (size_t i = 0; i < NUM_PARTICLES; i++){
        y[i] += y_speed[i];

        int jitter = rand() % 3 - 1;

        x[i] += jitter + wind;
        x[i] = x[i] % (MAX_X + 1);
        if (y[i] >= MAX_Y){
            spawn(i);
        }
    }
}


void ParticleSystem::render(){
    for (size_t i = 0; i < NUM_PARTICLES; i++) {
        glPutPixel(x[i], y[i], RGB15(31, 31, 31));
    }
}
