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

int xVel = 0;
int yVel = 0;
int homeScore = 0;
int awayScore = 0;
screens currentScreen = opening;
Rect leftPaddle;
Rect rightPaddle;
Rect title(black, {400, 250}, {100, 25}, "PONG");
Rect rules1(black, {400, 300}, {100, 25}, "First to five wins!");
Rect rules2(black, {400, 350}, {100, 25}, "Controls:");
Rect rules3(black, {400, 375}, {100, 25}, "Home: w / s        Away: up / down");
Rect rules4(black, {400, 475}, {100, 25}, "Press 'b' to begin");
Rect currentScore(black, {400, 50}, {100, 25}, "Home   " + to_string(homeScore) + "   |   " + to_string(awayScore) + "   Away");
Rect conclusion(black, {400, 250}, {100, 25}, "Thanks for playing!");
Rect finalScores(black, {400, 350}, {100, 25}, "HOME " + to_string(homeScore) + " - " + to_string(awayScore) + " AWAY");
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
    int initialLR = rand() % 2;
    int initialUD = rand() % 9;

    if (initialLR == 0) {
        ball.setXVelocity(-5);
    }
    if (initialLR == 1) {
        ball.setXVelocity(5);
    }

    if (initialUD == 0) {
        ball.setYVelocity(-1);
    }
    if (initialUD == 1) {
        ball.setYVelocity(1);
    }
    if (initialUD == 2) {
        ball.setYVelocity(-2);
    }
    if (initialUD == 3) {
        ball.setYVelocity(2);
    }
    if (initialUD == 4) {
        ball.setYVelocity(-3);
    }
    if (initialUD == 5) {
        ball.setYVelocity(3);
    }
    if (initialUD == 6) {
        ball.setYVelocity(-4);
    }
    if (initialUD == 7) {
        ball.setYVelocity(4);
    }
    if (initialUD == 8) {
        ball.setYVelocity(0);
    }
}

void init() {
    width = 800;
    height = 800;
    srand(time(0));
    initPaddles();
    initBall();
    initBallDirection();
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

        title.drawText();
        rules1.drawText();
        rules2.drawText();
        rules3.drawText();
        rules4.drawText();

        glFlush();  // Render now

    } else if (currentScreen == play) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        currentScore.drawText();

        leftPaddle.draw();
        rightPaddle.draw();

        ball.draw();

        if (ball.getLeftX() < 0) {
            currentScore.setAwayScore(currentScore.getAwayScore() + 1);
            init();
        }
        if (ball.getRightX() > 800) {
            currentScore.setHomeScore(currentScore.getHomeScore() + 1);
            init();
        }
        if (homeScore >= 5 || awayScore >= 5) {
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

        conclusion.drawText();
        finalScores.drawText();

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
        if (leftPaddle.getTopY() > 0) {
            leftPaddle.moveY(-20);
        }
    }
    if (key == 's') {
        if (leftPaddle.getBottomY() < 800) {
            leftPaddle.moveY(20);
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if (rightPaddle.getBottomY() < 800)
            rightPaddle.moveY(20);
            break;
        case GLUT_KEY_UP:
            if (rightPaddle.getTopY() > 0) {
                rightPaddle.moveY(-20);
            }
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

    // Handle how ball bounces off top and bottom
    if (ball.getTopY() < 0) {
        ball.bounceY();
    } else if (ball.getBottomY() > 800) {
        ball.bounceY();
    }

//    // Handle how ball bounces off left paddle
//    if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getTopY() &&
//                                                     ball.getCenterY() < leftPaddle.getTopY() + 40)) {
//        ball.bounceX();
//        ball.setXVelocity(3);
//        ball.setYVelocity(-4);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getTopY() + 40 &&
//                                                       ball.getCenterY() < leftPaddle.getTopY() + 80)) {
//        ball.bounceX();
//        ball.setXVelocity(3.5);
//        ball.setYVelocity(-3);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getTopY() + 80 &&
//                                                       ball.getCenterY() < leftPaddle.getTopY() + 120)) {
//        ball.bounceX();
//        ball.setXVelocity(4);
//        ball.setYVelocity(-2);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getTopY() + 120 &&
//                                                       ball.getCenterY() < leftPaddle.getTopY() + 160)) {
//        ball.bounceX();
//        ball.setXVelocity(4.5);
//        ball.setYVelocity(-1);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getTopY() + 160 &&
//                                                     ball.getCenterY() < leftPaddle.getBottomY() - 160)) {
//        ball.bounceX();
//        ball.setXVelocity(5);
//        ball.setYVelocity(0);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getBottomY() - 160 &&
//                                                            ball.getCenterY() < leftPaddle.getBottomY() - 120)) {
//        ball.bounceX();
//        ball.setXVelocity(4.5);
//        ball.setYVelocity(1);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getBottomY() - 120 &&
//                                                            ball.getCenterY() < leftPaddle.getBottomY() - 80)) {
//        ball.bounceX();
//        ball.setXVelocity(4);
//        ball.setYVelocity(2);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getBottomY() - 80 &&
//                                                            ball.getCenterY() < leftPaddle.getBottomY() - 40)) {
//        ball.bounceX();
//        ball.setXVelocity(3.5);
//        ball.setYVelocity(3);
//    } else if (ball.isOverlappingLeftPaddle(leftPaddle) && (ball.getCenterY() > leftPaddle.getBottomY() - 40 &&
//                                                            ball.getCenterY() < leftPaddle.getBottomY())) {
//        ball.bounceX();
//        ball.setXVelocity(3);
//        ball.setYVelocity(4);
//    }
//
//    // Handle how ball bounces off right paddle
//    if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getTopY() &&
//                                                     ball.getCenterY() < rightPaddle.getTopY() + 40)) {
//        ball.bounceX();
//        ball.setYVelocity(-4);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getTopY() + 40 &&
//                                                            ball.getCenterY() < rightPaddle.getTopY() + 80)) {
//        ball.bounceX();
//        ball.setYVelocity(-3);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getTopY() + 80 &&
//                                                            ball.getCenterY() < rightPaddle.getTopY() + 120)) {
//        ball.bounceX();
//        ball.setYVelocity(-2);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getTopY() + 120 &&
//                                                            ball.getCenterY() < rightPaddle.getTopY() + 160)) {
//        ball.bounceX();
//        ball.setYVelocity(-1);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getTopY() + 160 &&
//                                                            ball.getCenterY() < rightPaddle.getBottomY() - 160)) {
//        ball.bounceX();
//        ball.setYVelocity(0);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getBottomY() - 160 &&
//                                                            ball.getCenterY() < rightPaddle.getBottomY() - 120)) {
//        ball.bounceX();
//        ball.setYVelocity(1);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getBottomY() - 120 &&
//                                                            ball.getCenterY() < rightPaddle.getBottomY() - 80)) {
//        ball.bounceX();
//        ball.setYVelocity(2);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getBottomY() - 80 &&
//                                                            ball.getCenterY() < rightPaddle.getBottomY() - 40)) {
//        ball.bounceX();
//        ball.setYVelocity(3);
//    } else if (ball.isOverlappingRightPaddle(rightPaddle) && (ball.getCenterY() > rightPaddle.getBottomY() - 40 &&
//                                                            ball.getCenterY() < rightPaddle.getBottomY())) {
//        ball.bounceX();
//        ball.setYVelocity(4);
//    }

    if (ball.isOverlappingLeftPaddle(leftPaddle)){
        ball.bounceX();
    }

    if (ball.isOverlappingRightPaddle(rightPaddle)) {
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