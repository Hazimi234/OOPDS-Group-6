#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <string>
#include <ostream>

class GenericRobot; // Forward declaration

class Ability {
public:
    virtual void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log) = 0;
    virtual bool isScoutBot() const { return false; } // For type check
    virtual ~Ability() = default;
};

#endif
