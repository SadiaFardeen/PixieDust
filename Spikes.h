#ifndef SPIKES_H
#define SPIKES_H

#include <GL/glut.h>

class Spike {
public:
    float x, y;
    float width, height;

    Spike();
    Spike(float x_new, float y_new);

    void draw();
    void moveLeft(float speed);
};

void initSpikes();
void drawSpikes();
void updateSpikes();

// collision check with player
bool spikeCollision(float px, float py, float pw, float ph);

#endif

