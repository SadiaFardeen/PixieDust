#include "Player.h"
#include "shapes.h"
#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h> // for sound

Player::Player() {
    x = 100;
    y = 200;
    width = 40;
    height = 60;
    velocityY = 0;
    isJumping = false;
    isDucking = false;
}

void Player::update(std::vector<GameObject>& platforms) {
    // Gravity
    y += velocityY;
    velocityY -= GRAVITY;

    // Ducking Size
    if (isDucking) height = 30;
    else height = 60;

    float playerBottom = y - height / 2;
    float playerLeft = x - width / 2;
    float playerRight = x + width / 2;

    // Platform Collision (Only if falling)
    if (velocityY < 0) {
        for (size_t i = 0; i < platforms.size(); i++) {
            GameObject& p = platforms[i];
            float platformTop = p.y + p.h / 2;
            float platformLeft = p.x - p.w / 2;
            float platformRight = p.x + p.w / 2;

            // Check if player is horizontally within the platform
            if (playerRight > platformLeft && playerLeft < platformRight) {
                // Check if feet are crossing the top edge
                if (playerBottom <= platformTop && playerBottom > platformTop - 15) {
                    y = platformTop + height / 2; // Snap to top
                    velocityY = 0;
                    isJumping = false;
                }
            }
        }
    }

    // Floor to stand (y=50)
    if (y < 50 + height / 2) {
        y = 50 + height / 2;
        velocityY = 0;
        isJumping = false;
    }
}

void Player::draw() {
    float skinR = 1.0f, skinG = 0.8f, skinB = 0.6f;
    float shirtR = 0.9f, shirtG = 0.1f, shirtB = 0.1f; // Red
    float pantsR = 0.1f, pantsG = 0.1f, pantsB = 0.8f; // Blue
    float shoeR  = 0.2f, shoeG  = 0.2f, shoeB  = 0.2f; // Dark Grey

    if (isDucking) { // Ducking Pose
        // Shoes
        RectangleM(x - 14, y - 13, 12, 6, shoeR, shoeG, shoeB);
        RectangleM(x + 14, y - 13, 12, 6, shoeR, shoeG, shoeB);

        // Legs
        RectangleM(x - 12, y - 8, 10, 8, pantsR, pantsG, pantsB);
        RectangleM(x + 12, y - 8, 10, 8, pantsR, pantsG, pantsB);

        // Body
        RectangleM(x, y, 36, 14, shirtR, shirtG, shirtB);

        // Head
        Circle(x, y + 10, 10, skinR, skinG, skinB);

        // Eye (Looking forward)
        RectangleM(x + 6, y + 10, 6, 2, 0, 0, 0);

    } else { // Standing Pose

        // Shoes
        RectangleM(x - 10, y - 28, 12, 8, shoeR, shoeG, shoeB);
        RectangleM(x + 10, y - 28, 12, 8, shoeR, shoeG, shoeB);

        // Legs
        RectangleM(x - 10, y - 15, 10, 20, pantsR, pantsG, pantsB);
        RectangleM(x + 10, y - 15, 10, 20, pantsR, pantsG, pantsB);

        // Body
        RectangleM(x, y + 5, 32, 24, shirtR, shirtG, shirtB);

        // Arms
        RectangleM(x - 18, y + 5, 8, 20, shirtR, shirtG, shirtB);
        RectangleM(x + 18, y + 5, 8, 20, shirtR, shirtG, shirtB);

        // Head
        Circle(x, y + 24, 12, skinR, skinG, skinB);

        // Eye
        RectangleM(x + 6, y + 26, 6, 2, 0, 0, 0);
    }
}

void Player::jump() {
    if (!isJumping) {
        PlaySound(TEXT("jump.wav"), NULL, SND_FILENAME | SND_ASYNC);
        velocityY = JUMP_FORCE;
        isJumping = true;
    }
}

void Player::moveRight() { x += MOVE_SPEED; }
void Player::moveLeft() { x -= MOVE_SPEED; }
void Player::duck(bool state) { isDucking = state; }
