#include "Robot.h"

Robot::Robot(string name, int x, int y)
    : name(name), x(x), y(y), isDestroyed(false) {}

void Robot::displayStatus() const {
    cout << "[" << name << "] Position: (" << x << ", " << y << ")"
         << ", Status: " << (isDestroyed ? "Destroyed" : "Active") << endl;
}

string Robot::getName() const { return name; }
int Robot::getX() const { return x; }
int Robot::getY() const { return y; }
bool Robot::getIsDestroyed() const { return isDestroyed; }

void Robot::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
