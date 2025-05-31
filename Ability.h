#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <string>
#include <ostream>
#include "Robot.h"
class GenericRobot; // Forward declaration

class Ability
{
public:
    virtual void activate(GenericRobot *robot, std::vector<std::vector<char>> &battlefield, std::ostream &log, const std::vector<Robot*>& robots) = 0;

    // Category checkers
    virtual bool isScoutBot() const { return false; }
    virtual bool isThirtyShotBot() const { return false; }
    virtual bool isSemiAutoBot() const { return false; }
    virtual bool isLongShotBot() const { return false; }
    virtual bool isTrackBot() const { return false; }
    virtual bool isHideBot() const { return false; }
    virtual bool isJumpBot() const { return false; } 
    virtual bool hasUses() const { return false; } // Default implementation

    virtual bool isShootingAbility() const { return false; }
    virtual bool isMovingAbility() const { return false; }
    virtual bool isSeeingAbility() const { return false; }

    virtual ~Ability() = default;
};

// --- Shooting Ability Base ---
class ShootingAbility : public Ability
{
public:
    bool isShootingAbility() const override { return true; }
};

// --- Moving Ability Base ---
class MovingAbility : public Ability
{
public:
    bool isMovingAbility() const override { return true; }
};

// --- Seeing Ability Base ---
class SeeingAbility : public Ability
{
public:
    bool isSeeingAbility() const override { return true; }
};

#endif
