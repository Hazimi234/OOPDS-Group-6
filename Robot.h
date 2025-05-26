#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Robot {
protected:
    string name;
    int x, y;
    bool isDestroyed;

public:
    Robot(string name, int x, int y);
    virtual ~Robot() {}

    virtual void performTurn(const vector<Robot*>& robots) = 0;
    virtual void takeDamage() = 0;
    virtual bool isHit() = 0;
    virtual void displayStatus() const;
    virtual Robot* checkForUpgrade() { return this; }

    string getName() const;
    int getX() const;
    int getY() const;
    bool getIsDestroyed() const;
    void setPosition(int newX, int newY);
};

#endif
