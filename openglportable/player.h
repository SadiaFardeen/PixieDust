#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>

// Global Variables
extern float playerx;
extern float playery;
extern float velocityY;

extern bool isDucking;
extern bool isJumping;

// Physics constants
extern const float gravity;
extern const float jumpSpeed;
extern const float groundY;


// Drawing functions
void drawHead();
void drawBody();
void drawShoes();

// GLUT callbacks
void display();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void update(int value);

// Initialization
void init();

#endif

