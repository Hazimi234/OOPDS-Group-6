#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class ThirtyShotBot : public Ability {
private:
    bool used = false;  // One-time activation

public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& /*robots*/) override;

    bool isThirtyShotBot() const override { return true; }
};

#endif
