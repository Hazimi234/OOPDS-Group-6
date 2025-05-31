#ifndef SEMIAUTOBOT_H
#define SEMIAUTOBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class SemiAutoBot : public Ability {
public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& /*robots*/) override;
    bool isSemiAutoBot() const override { return true; }
};

#endif
