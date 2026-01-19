#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <GL/glut.h>

class Platform {
public:
    float left, right, top, bottom;
    float red, green, blue;

    Platform() {}

    Platform(float l, float r, float t, float b, float rd, float gn, float bl);
    void draw();
    void moveLeft(float speed);
};

void initEnvironment();
void drawEnvironment();
void updateEnvironment();

#endif
