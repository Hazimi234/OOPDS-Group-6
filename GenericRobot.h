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
#include "Ability.h"
#include <utility>



class GenericRobot : public Robot {
private:
    std::vector<Robot*> trackedEnemies;
public:
    GenericRobot(std::string t, std::string n, std::string xStr, std::string yStr);

    void think(std::ofstream& log) override;
    bool look(int dx, int dy, const std::vector<std::vector<char>>& battlefield, std::ofstream& log) override;
    void fire(int dx, int dy, std::vector<std::vector<char>>& battlefield,
              std::vector<Robot*>& robots, std::ofstream& log) override;
    void move(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) override;
    void takeTurn(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots, std::ofstream& log) override;
    void assignRandomUpgrade(std::ofstream& log);
    void checkAndResetIfNoUpgrades();
    Ability* movingAbility= nullptr;
    Ability* seeingAbility= nullptr;
    Ability* shootingAbility= nullptr;
    bool scoutVisionThisTurn = false;

    bool hasScoutVision() const { return scoutVisionThisTurn; }
    void enableScoutVision(bool state) { scoutVisionThisTurn = state; }
    Ability* getMovingAbility() const { return movingAbility; }
    Ability* getSeeingAbility() const { return seeingAbility; }
    Ability* getShootingAbility() const { return shootingAbility; }
    void setMovingAbility(Ability* a) { movingAbility = a; }
    void setSeeingAbility(Ability* a) { seeingAbility = a; }
    void setShootingAbility(Ability* a) { shootingAbility = a; }

    bool isEnemyTracked(Robot* enemyRobot) const;
    void addTrackedEnemy(Robot* enemy) {
        if (!isEnemyTracked(enemy)) {
            trackedEnemies.push_back(enemy);
        }
    }

    Robot* getTrackedEnemy() const {
        return trackedEnemies.empty() ? nullptr : trackedEnemies[0];
    }

    void kill(std::vector<std::vector<char>>& battlefield, std::ofstream& log) override;

    ~GenericRobot();

};



#endif // GENERICROBOT_H
