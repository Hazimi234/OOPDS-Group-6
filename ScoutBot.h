#ifndef SCOUTBOT_H
#define SCOUTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class ScoutBot : public Ability {
private:
    int usesLeft = 3;

public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) override;

    bool isScoutBot() const override { return true; }

    void decrementUse() { usesLeft--; }
    bool hasUses() const { return usesLeft > 0; }
};

#endif
