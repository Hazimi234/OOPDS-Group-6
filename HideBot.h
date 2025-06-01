/**********|**********|**********|
Program: HideBot.h
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "Ability.h"
#include "GenericRobot.h"

using namespace std;

//inherits from Ability class
class HideBot : public Ability
{
private:
    //hidebot has 3 uses remaining
    int usesRemaining = 3;

public:
    bool tryHide(GenericRobot *robot, ostream &log); // attempt to hide when targeted
    bool isHideBot() const override { return true; }
    int getUsesRemaining() const { return usesRemaining; }
    void activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/) override;
};

#endif
