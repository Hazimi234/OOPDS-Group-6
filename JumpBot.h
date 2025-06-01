/**********|**********|**********|
Program: JumpBot.h 
Course: Data Structures and Algorithms
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef JUMPBOT_H
#define JUMPBOT_H


#include "Ability.h"
#include "GenericRobot.h"
#include <vector>
#include <iostream>
#include <cstdlib>


class JumpBot : public Ability {
private:
    int jumpsRemaining=3;
public:
    JumpBot();
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield,
                  std::ostream& log, const std::vector<Robot*>& robots) override;
    bool hasUses() const override { return jumpsRemaining > 0; }            
    bool isJumpBot() const override;
};

#endif // JUMPBOT_H
