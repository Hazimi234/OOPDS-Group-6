#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class SemiAutoBot : public Ability {
public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) override;
    bool isSemiAutoBot() const override { return true; }
    std::string getName() const override { return "SemiAutoBot"; }
};

#endif
