/**********|**********|**********|
Program: ThirtyShotBot.h
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

class ThirtyShotBot : public Ability
{
private:
    bool used = false; // One-time activation

public:
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/) override;

    bool isThirtyShotBot() const override { return true; }
};

#endif
