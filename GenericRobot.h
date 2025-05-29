/**********|**********|**********|
Program: GenericRobot.h  
Course: Data Structures and Algorithms
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include <iostream>
#include <vector>
#include <string>
#include "Robot.h"

class GenericRobot : public Robot {
public:
    GenericRobot(std::string t, std::string n, std::string xStr, std::string yStr);

    void think(std::ofstream& log) override;
    bool look(int dx, int dy, const std::vector<std::vector<char>>& battlefield, std::ofstream& log) override;
    void fire(int dx, int dy, std::vector<std::vector<char>>& battlefield,
              std::vector<Robot*>& robots, std::ofstream& log) override;
    void move(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) override;
    void takeTurn(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) override;
};

#endif // GENERICROBOT_H
