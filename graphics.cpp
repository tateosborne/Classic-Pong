#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <cmath>
#include <unistd.h>

using namespace std;

enum screens {
    opening,
    play,
    summary
};
enum state {
    stop,
    go
};

GLdouble width, height;
int wd;
const color white(1, 1, 1);
const color black(0, 0, 0);

int homeScore = 0;
int awayScore = 0;
double deltaXVel = 0;
screens currentScreen = opening;
state mode = stop;
Rect leftPaddle;
Rect rightPaddle;
Rect title(black, {400, 250}, {100, 25}, "PONG");
Rect rules1(black, {400, 300}, {100, 25}, "First to five wins!");
Rect rules2(black, {400, 350}, {100, 25}, "Controls:");
Rect rules3(black, {400, 375}, {100, 25}, "Home: w / s        Away: up / down");
Rect rules4(black, {400, 475}, {100, 25}, "Press 'b' to begin");
Rect pressSpace(black, {400, 575}, {100, 25}, "[ press 'space bar' when you're ready ]");
Rect conclusion(black, {400, 250}, {100, 25}, "Thanks for playing!");
Circle ball;

void initPaddles() {
    leftPaddle.setCenter(5, 400);
    leftPaddle.setSize(10, 80);
    leftPaddle.setColor(white);

    rightPaddle.setCenter(795, 400);
    rightPaddle.setSize(10, 80);
    rightPaddle.setColor(white);
}

void initBall() {
    ball.setCenter(400, 400);
    ball.setRadius(5);
    ball.setColor(white);
}

void initBallDirection() {
    int initialVelocity = rand() % 24;

    // Up down velocity
    if (initialVelocity == 0) {
        ball.setXVelocity(sqrt(24.75));
        ball.setYVelocity(0.5);
    }
    if (initialVelocity == 1) {
        ball.setXVelocity(-sqrt(24.75));
        ball.setYVelocity(0.5);
    }
    if (initialVelocity == 2) {
        ball.setXVelocity(sqrt(24.75));
        ball.setYVelocity(-0.5);
    }
    if (initialVelocity == 3) {
        ball.setXVelocity(-sqrt(24.75));
        ball.setYVelocity(-0.5);
    }

    if (initialVelocity == 4) {
        ball.setXVelocity(sqrt(24));
        ball.setYVelocity(1);
    }
    if (initialVelocity == 5) {
        ball.setXVelocity(-sqrt(24));
        ball.setYVelocity(1);
    }
    if (initialVelocity == 6) {
        ball.setXVelocity(sqrt(24));
        ball.setYVelocity(-1);
    }
    if (initialVelocity == 7) {
        ball.setXVelocity(-sqrt(24));
        ball.setYVelocity(-1);
    }

    if (initialVelocity == 8) {
        ball.setXVelocity(sqrt(21));
        ball.setYVelocity(2);
    }
    if (initialVelocity == 9) {
        ball.setXVelocity(-sqrt(21));
        ball.setYVelocity(2);
    }
    if (initialVelocity == 10) {
        ball.setXVelocity(sqrt(21));
        ball.setYVelocity(-2);
    }
    if (initialVelocity == 11) {
        ball.setXVelocity(-sqrt(21));
        ball.setYVelocity(-2);
    }

    if (initialVelocity == 12) {
        ball.setXVelocity(sqrt(16));
        ball.setYVelocity(3);
    }
    if (initialVelocity == 13) {
        ball.setXVelocity(-sqrt(16));
        ball.setYVelocity(3);
    }
    if (initialVelocity == 14) {
        ball.setXVelocity(sqrt(16));
        ball.setYVelocity(-3);
    }
    if (initialVelocity == 15) {
        ball.setXVelocity(-sqrt(16));
        ball.setYVelocity(-3);
    }

    if (initialVelocity == 16) {
        ball.setXVelocity(sqrt(9));
        ball.setYVelocity(4);
    }
    if (initialVelocity == 17) {
        ball.setXVelocity(-sqrt(9));
        ball.setYVelocity(4);
    }
    if (initialVelocity == 18) {
        ball.setXVelocity(sqrt(9));
        ball.setYVelocity(-4);
    }
    if (initialVelocity == 19) {
        ball.setXVelocity(-sqrt(9));
        ball.setYVelocity(-4);
    }

    if (initialVelocity == 20) {
        ball.setXVelocity(sqrt(4.75));
        ball.setYVelocity(4.5);
    }
    if (initialVelocity == 21) {
        ball.setXVelocity(-sqrt(4.75));
        ball.setYVelocity(4.5);
    }
    if (initialVelocity == 22) {
        ball.setXVelocity(sqrt(4.75));
        ball.setYVelocity(-4.5);
    }
    if (initialVelocity == 23) {
        ball.setXVelocity(-sqrt(4.75));
        ball.setYVelocity(-4.5);
    }

}

void init() {
    width = 800;
    height = 800;
    srand(time(nullptr));
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

        Rect currentScore(black, {400, 50}, {100, 25},
                          "Home   " + to_string(homeScore) + "   |   " + to_string(awayScore) + "   Away");
        currentScore.drawText();
        pressSpace.drawText();

        leftPaddle.draw();
        rightPaddle.draw();
        ball.draw();

        if (mode == go) {
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

            glClear(GL_COLOR_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            Rect currentScore(black, {400, 50}, {100, 25},
                              "Home   " + to_string(homeScore) + "   |   " + to_string(awayScore) + "   Away");
            currentScore.drawText();

            leftPaddle.draw();
            rightPaddle.draw();
            ball.draw();

            if (ball.getRightX() < 0) {
                mode = stop;
                pressSpace.drawText();
                awayScore++;
                init();
            }
            if (ball.getLeftX() > 800) {
                mode = stop;
                pressSpace.drawText();
                homeScore++;
                init();
            }
        }

        glFlush();  // Render now

    }

    if (homeScore >= 5 || awayScore >= 5) {
        currentScreen = summary;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        sleep(1);

        Rect finalScores(black, {400, 350}, {100, 25}, "HOME " + to_string(homeScore) + " - " + to_string(awayScore) + " AWAY");
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
        sleep(1);
        currentScreen = play;
    }
    if (key == 32 && mode == stop && currentScreen == play) {
        mode = go;
    }
    if (key == 'w') {
        if (leftPaddle.getTopY() > 0) {
            leftPaddle.moveY(-24);
        }
    }
    if (key == 's') {
        if (leftPaddle.getBottomY() < 800) {
            leftPaddle.moveY(24);
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if (rightPaddle.getBottomY() < 800)
            rightPaddle.moveY(24);
            break;
        case GLUT_KEY_UP:
            if (rightPaddle.getTopY() > 0) {
                rightPaddle.moveY(-24);
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

void ballTimer(int dummy) {
    if (mode == go) {
        ball.move(ball.getXVelocity(), ball.getYVelocity());

        // Handle how ball bounces off top and bottom
        if (ball.getTopY() < 0) {
            ball.bounceY();
        } else if (ball.getBottomY() > 800) {
            ball.bounceY();
        }

        // Handle how ball bounces off left paddle
        if (ball.isOverlappingLeftPaddle(leftPaddle)) {
            ball.bounceX();

            deltaXVel = 0.5;
            ball.setXVelocity(ball.getXVelocity() + deltaXVel);
        }

        // Handle how ball bounces off right paddle
        if (ball.isOverlappingRightPaddle(rightPaddle)) {
            ball.bounceX();

            deltaXVel = -0.5;
            ball.setXVelocity(ball.getXVelocity() + deltaXVel);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, ballTimer, dummy);
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
    glutTimerFunc(0, ballTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}