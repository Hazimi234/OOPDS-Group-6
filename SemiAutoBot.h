#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

class SemiAutoBot : public Ability
{
public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/) override;
    bool isSemiAutoBot() const override { return true; }
};

#endif
