#ifndef SCOUTBOT_H
#define SCOUTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

class ScoutBot : public Ability
{
private:
    int usesLeft = 3;

public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots) override;
    bool isScoutBot() const override { return true; }

    void decrementUse() { usesLeft--; }
    bool hasUses() const { return usesLeft > 0; }
};

#endif
