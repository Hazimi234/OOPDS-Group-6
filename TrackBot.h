#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "Ability.h" // Assuming Ability is the base class
#include "GenericRobot.h"
#include <vector>
#include <iostream>

using namespace std;

class TrackBot : public Ability
{
private:
    int usesLeft = 3;

public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots) override;

    bool isTrackBot() const override { return true; }

    void decrementUse() { usesLeft--; }
    bool hasUses() const { return usesLeft > 0; }
};

#endif
