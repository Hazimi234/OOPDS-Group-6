/**********|**********|**********|
Program: HideBot.cpp
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#include "HideBot.h"
#include <iostream>

using namespace std;

bool HideBot::tryHide(GenericRobot *robot, ostream &log)
{
    cout << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";
    log << robot->getName() << " used HideBot to avoid being hit! (" << usesRemaining - 1 << " left)\n";

    usesRemaining--;

    if (usesRemaining <= 0)
    {
        cout << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";
        log << robot->getName() << "'s HideBot ability expired and reverted to GenericRobot.\n";

        delete robot->ability;
        robot->ability = nullptr;
    }

    return true; // dodged the attack
}

void HideBot::activate(GenericRobot *robot, vector<vector<char>> &battlefield, ostream &log, const vector<Robot *> & /*robots*/)
{
}
