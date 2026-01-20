#ifndef SPIKES_H
#define SPIKES_H

#include <GL/glut.h>
#include <vector>

class Spike {
public:
    float x, y;
    float width, height;

    Spike(float xPos, float yPos);
    void draw();
    void moveLeft(float speed);
};

void initSpikes();
void drawSpikes();
void updateSpikes();
bool spikeCollision(float px, float py, float pw, float ph);

#endif
