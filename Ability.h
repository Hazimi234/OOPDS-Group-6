#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <string>
#include <ostream>
#include "Robot.h"
class GenericRobot; // Forward declaration

class Ability {
public:
    virtual void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& robots) = 0;
    virtual bool isScoutBot() const { return false; } // For type check
    virtual bool isTrackBot() const { return false; }
    virtual bool isJumpBot() const { return false; } // For type check 
    virtual bool hasUses() const { return false; } // Default implementation
    virtual ~Ability() = default;
};

#endif
