#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class LongShotBot : public Ability {
public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) override {}
    
    bool isLongShotBot() const override { return true; }
};

#endif
