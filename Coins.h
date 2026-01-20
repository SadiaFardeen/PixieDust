#ifndef COINS_H
#define COINS_H

#include <GL/glut.h>

class Coin {
public:
    float x, y, size;
    bool isCollected;

    Coin() {}
    Coin(float x_new, float y_new);
    void draw();
    void moveLeft(float speed);
};

void initCoins();
void drawCoins();
void updateCoins();

#endif
