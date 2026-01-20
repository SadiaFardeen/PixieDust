#include <GL/glut.h>
#include "GroundSystem.h"

// Ground variables
static float groundY = -0.8f;
static float groundOffset = 0.0f;
static float groundSpeed = 0.01f;

// Tree positions
static float treePositions[] = {-0.8f, -0.2f, 0.5f, 1.2f};

// Draw a single tree
void drawTree(float x) {
    // Trunk
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f, groundY);
    glVertex2f(x + 0.02f, groundY);
    glVertex2f(x + 0.02f, groundY + 0.15f);
    glVertex2f(x - 0.02f, groundY + 0.15f);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.08f, groundY + 0.15f);
    glVertex2f(x + 0.08f, groundY + 0.15f);
    glVertex2f(x, groundY + 0.35f);
    glEnd();
}

// Draw ground and trees
void drawGround() {
    // Ground
    glColor3f(0.3f, 0.7f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f + groundOffset, groundY);
    glVertex2f( 3.0f + groundOffset, groundY);
    glVertex2f( 3.0f + groundOffset, -1.0f);
    glVertex2f(-1.0f + groundOffset, -1.0f);
    glEnd();

    // Trees
    for (float x : treePositions) {
        drawTree(x + groundOffset);
    }
}

// Update movement
void updateGround() {
    groundOffset -= groundSpeed;

    // Loop ground
    if (groundOffset <= -2.0f)
        groundOffset = 0.0f;
}

// Expose ground Y
float getGroundY() {
    return groundY;
}
