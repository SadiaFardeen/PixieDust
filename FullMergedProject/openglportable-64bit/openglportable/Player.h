#ifndef PLAYER_H
#define PLAYER_H

#include "shapes.h"
#include <vector>

class Player {
public:
    float x, y;
    float width, height;
    float velocityY;
    bool isJumping;
    bool isDucking;

    // Physics Constants
    const float GRAVITY = 0.8f;
    const float JUMP_FORCE = 13.0f;
    const float MOVE_SPEED = 5.0f;

    Player();

    void update(std::vector<GameObject>& platforms);
    void draw();
    void jump();
    void moveRight();
    void moveLeft();
    void duck(bool state);
};

#endif
