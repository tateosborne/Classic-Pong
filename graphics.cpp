#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include <random>

using namespace std;

enum screens {
    opening,
    play,
    summary
};

GLdouble width, height;
int wd;
const color white(1, 1, 1);
const color black(0, 0, 0);

int initialMove;
int xVel = 0;
int yVel = 0;
int homeScore = 0;
int awayScore = 0;
screens currentScreen = opening;
Rect leftPaddle;
Rect rightPaddle;
Rect title(black, {400, 350}, {100, 50}, "PONG (press 'b' to begin)");
Rect rules1(black, {400, 450}, {100, 50}, "first to five wins!");
Rect rules2(black, {400, 550}, {100, 50}, "Home/Left: 'w', 's'   ;   Away/Right: 'up arrow', 'down arrow'");
Rect currentScore(black, {400, 50}, {100, 50}, "Home   " + to_string(homeScore) + "   |   " + to_string(awayScore) + "   Away");
Rect conclusion(black, {400, 350}, {100, 50}, "Thanks for playing!");
Rect finalScores(black, {400, 450}, {100, 50}, "HOME " + to_string(homeScore) + " - " + to_string(awayScore) + " AWAY");
Circle ball;

void initPaddles() {
    leftPaddle.setCenter(5, 400);
    leftPaddle.setSize(10, 75);
    leftPaddle.setColor(white);

    rightPaddle.setCenter(795, 400);
    rightPaddle.setSize(10, 75);
    rightPaddle.setColor(white);
}

void initBall() {
    ball.setCenter(400, 400);
    ball.setRadius(5);
    ball.setColor(white);
}

void initBallDirection() {
    int initialMove = rand() % 2;
}

void init() {
    width = 800;
    height = 800;
    srand(time(0));
    initPaddles();
    initBall();
    initBallDirection();

    if (initialMove == 0) {
        ball.setXVelocity(-5);
    }
    if (initialMove == 1) {
        ball.setXVelocity(5);
    }
}

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    if (currentScreen == opening) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        title.draw();
        rules1.draw();
        rules2.draw();

        glFlush();  // Render now

    } else if (currentScreen == play) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        currentScore.draw();

        leftPaddle.draw();
        rightPaddle.draw();

        ball.draw();

        if (ball.getLeftX() < 0) {
            awayScore++;
            // wait half a second
            init();
        }
        if (ball.getRightX() > 800) {
            homeScore++;
            // wait half a second
            init();
        }
        if (homeScore >= 5 || awayScore >= 5) {
            // wait half a second
            currentScreen = summary;
        }

        glFlush();  // Render now

    } else if (currentScreen == summary) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        conclusion.draw();
        finalScores.draw();

        glFlush();  // Render now

    }
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 'b' && currentScreen == opening) {
        currentScreen = play;
    }
    if (key == 'w') {
        leftPaddle.moveY(-10);
    }
    if (key == 's') {
        leftPaddle.moveY(10);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            rightPaddle.moveY(10);
            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:
            rightPaddle.moveY(-10);
            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {

    ball.move(ball.getXVelocity(), ball.getYVelocity());

    if (ball.isOverlappingLeftPaddle(leftPaddle)) {
        ball.bounceX();
    } else if (ball.isOverlappingRightPaddle(rightPaddle)) {
        ball.bounceX();
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv); // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner

    wd = glutCreateWindow("PONG");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}