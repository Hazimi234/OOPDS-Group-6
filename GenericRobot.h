#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include "Robot.h"

class GenericRobot : public Robot {
private:
    int shellsRemaining;
    int upgrades;

public:
    GenericRobot(string name, int x, int y);
    void performTurn(const vector<Robot*>& robots) override;
    void takeDamage() override;
    bool isHit() override;
    void displayStatus() const override;

    void think();
    void look(int dx, int dy);
    void fire(int dx, int dy, const vector<Robot*>& robots);
    void move(int dx, int dy);
    Robot* checkForUpgrade() override;
};

#endif