#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

class ThirtyShotBot : public Ability
{
private:
    bool used = false; // One-time activation

public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/) override;

    bool isThirtyShotBot() const override { return true; }
};

#endif
