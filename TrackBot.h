#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "Ability.h" // Assuming Ability is the base class
#include "GenericRobot.h"
#include <vector>
#include <iostream>

class TrackBot : public Ability {
private:
    int usesLeft = 3;

public:
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& robots) override;

    bool isTrackBot() const override { return true; }

    void decrementUse() { usesLeft--; }
    bool hasUses() const { return usesLeft > 0; }
};

#endif
