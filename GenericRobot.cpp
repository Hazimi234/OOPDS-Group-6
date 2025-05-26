#include "GenericRobot.h"
#include "HideBot.h"
#include <cstdlib>
#include <ctime>

GenericRobot::GenericRobot(string name, int x, int y)
    : Robot(name, x, y), shellsRemaining(10), upgrades(0) {
    srand(time(0));
}

void GenericRobot::performTurn(const vector<Robot*>& robots) {
    think();
    int action = rand() % 3; // 0 = move, 1 = look, 2 = fire
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;

    if (action == 0) {
        move(dx, dy);
    } else if (action == 1) {
        look(dx, dy);
    } else if (action == 2) {
        fire(dx, dy, robots);
    }
}

void GenericRobot::takeDamage() {
    isDestroyed = true;
    cout << name << " was destroyed by damage." << endl;
}

bool GenericRobot::isHit() {
    return true;
}

void GenericRobot::displayStatus() const {
    Robot::displayStatus();
    cout << "Shells remaining: " << shellsRemaining << ", Upgrades: " << upgrades << endl;
}

void GenericRobot::think() {
    cout << name << " is thinking..." << endl;
}

void GenericRobot::look(int dx, int dy) {
    cout << name << " looks at direction (" << dx << ", " << dy << ")" << endl;
}

void GenericRobot::fire(int dx, int dy, const vector<Robot*>& robots) {
    if (dx == 0 && dy == 0 || isDestroyed) return;
    if (shellsRemaining <= 0) {
        isDestroyed = true;
        cout << name << " has no shells left and self-destructs." << endl;
        return;
    }
    shellsRemaining--;
    int tx = x + dx;
    int ty = y + dy;

    for (Robot* target : robots) {
        if (target == this || target->getIsDestroyed()) continue;
        if (target->getX() == tx && target->getY() == ty) {
            int chance = rand() % 100;
            if (chance < 70) {
                cout << name << " fires at (" << dx << ", " << dy << ") and hits " << target->getName() << "!" << endl;
                if (target->isHit()) {
                    target->takeDamage();
                    upgrades++;
                }
            } else {
                cout << name << " fires at (" << dx << ", " << dy << ") and misses " << target->getName() << "." << endl;
            }
            return;
        }
    }
    cout << name << " fires at (" << dx << ", " << dy << ") but hits nothing." << endl;
}

void GenericRobot::move(int dx, int dy) {
    x += dx;
    y += dy;
    cout << name << " moves to (" << x << ", " << y << ")" << endl;
}

Robot* GenericRobot::checkForUpgrade() {
    if (upgrades >= 1) {
        cout << name << " is upgrading to HideBot!" << endl;
        Robot* upgraded = new HideBot(name, x, y);
        delete this;
        return upgraded;
    }
    return this;
}