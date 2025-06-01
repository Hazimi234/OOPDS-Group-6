#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

class LongShotBot : public Ability
{
public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/) override {}

    bool isLongShotBot() const override { return true; }
};

#endif
