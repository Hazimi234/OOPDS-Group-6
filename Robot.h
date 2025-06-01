/**********|**********|**********|
Program: Robot.h
Course: Object Oriented Programming and Data Structures (OOPDS)
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>

using namespace std;

class Robot
{
protected:
    string type, name;
    int x, y;
    bool isRandom, alive;
    int lives, shells;
    bool tracked = false;

public:
    Robot(string t, string n, string xStr, string yStr);
    virtual ~Robot();

    void setShells(int s);
    int getShells() const;

    virtual void takeTurn(vector<vector<char>> &, vector<Robot *> &, ofstream &log) = 0;
    virtual void think(ofstream &log) = 0;
    virtual bool look(int dx, int dy, const vector<vector<char>> &, ofstream &log) = 0;
    virtual void fire(int dx, int dy, vector<vector<char>> &, vector<Robot *> &, ofstream &log) = 0;
    virtual void move(vector<vector<char>> &, vector<Robot *> &, ofstream &log) = 0;

    string getName() const;
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    bool isRandomPosition() const;
    bool isAlive() const;

    void kill(vector<vector<char>> &battlefield, ofstream &log);
    void respawn(vector<vector<char>> &battlefield, int rows, int cols, ofstream &log);

    bool canRespawn() const;

    void setTracked(bool status) { tracked = status; }
    bool isTracked() const { return tracked; }
};

#endif
