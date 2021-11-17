#include "graphics.h"
#include "rect.h"
#include <iostream>
using namespace std;

/********************* Dimensions Struct ********************/

dimensions::dimensions() : width(0), height(0) {}

dimensions::dimensions(double w, double h) : width(w), height(h) {}

ostream& operator << (ostream& outs, const dimensions &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}


Rect::Rect() : Shape(), size({0, 0}) {
}

Rect::Rect(dimensions size) : Shape() {
    setSize(size);
}

Rect::Rect(color fill) : Shape(fill), size({0, 0}) {
}

Rect::Rect(point2D center) : Shape(center), size({0, 0}) {
}

Rect::Rect(color fill, point2D center) : Shape(fill, center), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), size({0, 0}) {
}

Rect::Rect(double x, double y) : Shape(x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), size({0, 0}) {
}

Rect::Rect(color fill, double x, double y) : Shape(fill, x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), size({0, 0}) {
}

Rect::Rect(color fill, dimensions size) : Shape(fill) {
    setSize(size);
}

Rect::Rect(point2D center, dimensions size) : Shape(center) {
    setSize(size);
}

Rect::Rect(color fill, point2D center, dimensions size) : Shape(fill, center) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, dimensions size) : Shape(red, green, blue, alpha) {
    setSize(size);
}

Rect::Rect(double x, double y, dimensions size) : Shape(x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y, dimensions size) : Shape(red, green, blue, alpha, x, y) {
    setSize(size);
}

Rect::Rect(color fill, double x, double y, dimensions size) : Shape(fill, x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center, dimensions size) : Shape(red, green, blue, alpha, center) {
    setSize(size);
}
Rect::Rect(color fill, point2D center, dimensions size, string label) : Shape(fill, center) {
    setSize(size);
    this->label = label;
}

dimensions Rect::getSize() const {
    return size;
}

double Rect::getWidth() const {
    return size.width;
}

double Rect::getHeight() const {
    return size.height;
}

int Rect::getHomeScore() const {
    return homeScore;
}

int Rect::getAwayScore() const {
    return awayScore;
}

double Rect::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Rect::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Rect::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Rect::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Rect::setSize(dimensions size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Rect::setSize(double width, double height) {
    setSize({width, height});
}

void Rect::setWidth(double width) {
    setSize({width, size.height});
}

void Rect::setHeight(double height) {
    setSize({size.width, height});
}

void Rect::setHomeScore(int hS) {
    homeScore = hS;
}

void Rect::setAwayScore(int aS) {
    awayScore = aS;
}

void Rect::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Rect::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Rect::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}

bool Rect::isOverlapping(const Rect &r) const {
    bool overlap = true;
    if (r.getTopY() > getBottomY()) {
        overlap = false;
    }
    if (r.getBottomY() < getTopY()) {
        overlap = false;
    }
    if (r.getLeftX() > getRightX()) {
        overlap = false;
    }
    if (r.getRightX() < getLeftX()) {
        overlap = false;
    }
    return overlap;
}


void Rect::draw() const {
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2i(getLeftX(),getTopY());
    glVertex2i(getLeftX(),getBottomY());
    glVertex2i(getRightX(),getBottomY());
    glVertex2i(getRightX(),getTopY());
    glEnd();
}

void Rect::drawText() const {
    Rect::draw();
    glColor3f(1, 1, 1);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
}