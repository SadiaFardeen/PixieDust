#include <GL/glut.h>
#include "collisionDetection.cpp"
#include "ground_spikes.cpp"

const float GRAVITY = -0.8f;
const float JUMP_VELOCITY = 14.0f;
const float GROUND_Y = -200.0f;

struct Player {
    float x = -250;
    float y = GROUND_Y;
    float width = 40;
    float height = 60;
    float velocityY = 0;
    bool isJumping = false;
    bool isDead = false;
} player;

Rect playerRect() {
    return { player.x, player.y, player.width, player.height };
}

void drawPlayer() {
    if (player.isDead) {
        glColor3f(0.3, 0.3, 0.3); // gray when dead
    }
    else {
        glColor3f(0.2, 0.8, 0.2); // nice green
    }

    Rectangle0(player.x, player.y, player.width, player.height, 0.0f, 0.0f, 0.0f);

    // Simple face
    bresenhamCircle(player.x + player.width / 2, player.y + player.height - 15, 8, 1, 1, 1);
    // eyes
    bresenhamCircle(player.x + player.width / 2 - 4, player.y + player.height - 15, 3, 0, 0, 0);
    bresenhamCircle(player.x + player.width / 2 + 4, player.y + player.height - 15, 3, 0, 0, 0);
}

void updatePlayer(int value) {
    if (!player.isDead) {
        player.velocityY += GRAVITY;
        player.y += player.velocityY;

        // Ground collision
        if (player.y <= GROUND_Y) {
            player.y = GROUND_Y;
            player.velocityY = 0;
            player.isJumping = false;
        }

        // Check spike collision
        for (const auto& s : spikes) {
            Rect spikeRect = { s.x, s.y, s.width, s.height };
            if (collision(playerRect(), spikeRect)) {
                player.isDead = true;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updatePlayer, 0);
}