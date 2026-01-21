#ifndef SHAPES_H
#define SHAPES_H

#include <vector>

struct GameObject {
    float x, y, w, h;
    bool active;
    int timer;
};

struct Bullet {
    float x, y;
    float speed;
    bool active;
};

struct Cloud {
    float x, y;
    float speed;
    float scale;
};

struct Tree {
    float x, y; // Base position
    float speed; // Scrolling speed (for parallax)
    float scale; // Size multiplier
};
// ------------------

void RectangleM(float x, float y, float width, float height, float r, float g, float b);
void Circle(float x, float y, float radius, float r, float g, float b);
void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b);

#endif
