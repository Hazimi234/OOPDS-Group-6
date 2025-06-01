/**********|**********|**********|
Program: Ability.h
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <string>
#include <ostream>
#include "Robot.h"

using namespace std;

class GenericRobot; // Forward declaration

class Ability
{
public:
    virtual void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots) = 0;

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
