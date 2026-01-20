#include "player.h"
#include <cmath>

float playerx = 0.0f;
float playery = -0.5f;      // initial ground position
float velocityY = 0.0f;     // vertical velocity
bool isDucking = false;
bool isJumping = false;

const float gravity = -0.01f;
const float jumpSpeed = 0.14f;
const float groundY = -0.5f; // ground level


// Draw head (circle)
void drawHead() {
    glColor3f(1.0f, 0.8f, 0.6f);
    float radius = isDucking ? 0.05f : 0.08f;
    float cx = playerx;
    float cy = playery + 0.25f;


    // Face (Skin)
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(cx + radius * cos(angle),
            cy + radius * sin(angle));
    }
    glEnd();


    // Eyes (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON); // Left eye
    for (int i = 0; i < 50; i++)
    {
        float a = 2.0f * 3.14159f * i / 50;
        glVertex2f(cx - 0.025f + 0.012f * cos(a),
            cy + 0.015f + 0.012f * sin(a));
    }
    glEnd();

    glBegin(GL_POLYGON); // Right eye
    for (int i = 0; i < 50; i++)
    {
        float a = 2.0f * 3.14159f * i / 50;
        glVertex2f(cx + 0.025f + 0.012f * cos(a),
            cy + 0.015f + 0.012f * sin(a));
    }
    glEnd();


    // Pupils (Black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++)
    {
        float a = 2.0f * 3.14159f * i / 30;
        glVertex2f(cx - 0.025f + 0.006f * cos(a),
            cy + 0.015f + 0.006f * sin(a));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++)
    {
        float a = 2.0f * 3.14159f * i / 30;
        glVertex2f(cx + 0.025f + 0.006f * cos(a),
            cy + 0.015f + 0.006f * sin(a));
    }
    glEnd();


    // Nose
    glColor3f(1.0f, 0.7f, 0.5f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++)
    {
        float a = 2.0f * 3.14159f * i / 50;
        glVertex2f(cx + 0.018f * cos(a),
            cy - 0.005f + 0.012f * sin(a));
    }
    glEnd();


    // Mouth (Smile)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 200; i <= 340; i += 5)
    {
        float a = 3.14159f * i / 180.0f;
        glVertex2f(cx + 0.03f * cos(a),
            cy - 0.03f + 0.02f * sin(a));
    }
    glEnd();


    // Hat (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(cx - 0.09f, cy + 0.03f);
    glVertex2f(cx + 0.09f, cy + 0.03f);
    glVertex2f(cx + 0.06f, cy + 0.09f);
    glVertex2f(cx - 0.06f, cy + 0.09f);
    glEnd();

    // Hat brim
    glBegin(GL_QUADS);
    glVertex2f(cx - 0.1f, cy + 0.01f);
    glVertex2f(cx + 0.1f, cy + 0.01f);
    glVertex2f(cx + 0.1f, cy + 0.03f);
    glVertex2f(cx - 0.1f, cy + 0.03f);
    glEnd();
}

// Draw body, arms, legs
void drawBody() {
    // Shirt (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerx - 0.05f, playery + 0.1f);
    glVertex2f(playerx + 0.05f, playery + 0.1f);
    glVertex2f(playerx + 0.05f, playery);
    glVertex2f(playerx - 0.05f, playery);
    glEnd();

    // Overalls (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerx - 0.06f, playery);
    glVertex2f(playerx + 0.06f, playery);
    glVertex2f(playerx + 0.06f, playery - 0.12f);
    glVertex2f(playerx - 0.06f, playery - 0.12f);
    glEnd();

    // Arms (Skin)
    glColor3f(1.0f, 0.8f, 0.6f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(playerx - 0.05f, playery + 0.05f);
    glVertex2f(playerx - 0.14f, playery - 0.02f);

    glVertex2f(playerx + 0.05f, playery + 0.05f);
    glVertex2f(playerx + 0.14f, playery - 0.02f);
    glEnd();

    // Legs (Brown Shoes)
    glColor3f(0.4f, 0.2f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(playerx - 0.03f, playery - 0.12f);
    glVertex2f(playerx - 0.05f, playery - 0.25f);

    glVertex2f(playerx + 0.03f, playery - 0.12f);
    glVertex2f(playerx + 0.05f, playery - 0.25f);
    glEnd();
}


// Draw shoes
void drawShoes()
{
    // Shoe color (Dark Brown)
    glColor3f(0.3f, 0.15f, 0.05f);

    float shoeY = playery - 0.27f;

    // Left shoe
    glBegin(GL_QUADS);
        glVertex2f(playerx - 0.08f, shoeY);
        glVertex2f(playerx - 0.02f, shoeY);
        glVertex2f(playerx - 0.02f, shoeY + 0.04f);
        glVertex2f(playerx - 0.08f, shoeY + 0.04f);
    glEnd();

    // Right shoe
    glBegin(GL_QUADS);
        glVertex2f(playerx + 0.02f, shoeY);
        glVertex2f(playerx + 0.08f, shoeY);
        glVertex2f(playerx + 0.08f, shoeY + 0.04f);
        glVertex2f(playerx + 0.02f, shoeY + 0.04f);
    glEnd();
}

// Display
/*
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawHead();
    drawBody();
    drawShoes();
    glFlush();
}
*/

void keyboard(unsigned char key, int x, int y)
{

    //player up
    if (key == 'u') {
        playery += 0.05f;
    }

    // player down
    if (key == 'd') {
        playery -= 0.05f;
    }

    // player left move
    if (key == 'l') {
        playerx -= 0.05f;
    }

    // player right move
    if (key == 'r') {
        playerx += 0.05f;
    }

    // player jump
    if (key == 'j' && !isJumping) {
        velocityY = jumpSpeed;
        isJumping = true;
    }

    if (key == 's') {
        isDucking = true;
    }

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    if (key == 's') {
        isDucking = false;
    }
}

// Update player position for smooth jumping
void update(int value) {
    // Apply gravity
    if (isJumping || playery > groundY) {
        velocityY += gravity;
        playery += velocityY;

        // Land on ground
        if (playery <= groundY) {
            playery = groundY;
            velocityY = 0.0f;
            isJumping = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0); // ~60 FPS
}


// Initialization
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
}

