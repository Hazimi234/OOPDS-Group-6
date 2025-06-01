/**********|**********|**********|
Program: TrackBot.h
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef TRACKBOT_H
#define TRACKBOT_H

#include "Ability.h" // Assuming Ability is the base class
#include "GenericRobot.h"
#include <vector>
#include <iostream>

using namespace std;

class TrackBot : public Ability
{
private:
    int usesLeft = 3;

public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> &robots) override;

    bool isTrackBot() const override { return true; }

    void decrementUse() { usesLeft--; }
    bool hasUses() const { return usesLeft > 0; }
};

#endif
