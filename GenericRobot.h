/**********|**********|**********|
Program: GenericRobot.h
Course: Object Oriented Programming and Data Structures (OOPDS)
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

using namespace std;

class GenericRobot : public Robot
{
private:
    vector<Robot *> trackedEnemies;

public:
    GenericRobot(string t, string n, string xStr, string yStr);

    void think(ofstream &log) override;
    bool look(int dx, int dy, const vector<vector<char>> &battlefield, ofstream &log) override;
    void fire(int dx, int dy, vector<vector<char>> &battlefield,
              vector<Robot *> &robots, ofstream &log) override;
    void move(vector<vector<char>> &battlefield, vector<Robot *> &robots, ofstream &log) override;
    void takeTurn(vector<vector<char>> &battlefield, vector<Robot *> &robots, ofstream &log) override;

    Ability *ability = nullptr;
    bool scoutVisionThisTurn = false;

    bool hasScoutVision() const { return scoutVisionThisTurn; }
    void enableScoutVision(bool state) { scoutVisionThisTurn = state; }
    Ability *getAbility() const { return ability; }
    void setAbility(Ability *a) { ability = a; }

    bool isEnemyTracked(Robot *enemyRobot) const;
    void addTrackedEnemy(Robot *enemy)
    {
        if (!isEnemyTracked(enemy))
        {
            trackedEnemies.push_back(enemy);
        }
    }

    Robot *getTrackedEnemy() const
    {
        return trackedEnemies.empty() ? nullptr : trackedEnemies[0];
    }

    void resetToGeneric() {
        delete ability;
        ability = nullptr;
        shells = 10; // Reset to default shell count
        cout << "Robot destroyed! Resetting to GenericRobot." << endl; 
    }
    ~GenericRobot();
};

#endif // GENERICROBOT_H
