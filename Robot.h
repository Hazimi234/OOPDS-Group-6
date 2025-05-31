/**********|**********|**********|
Program: Robot.h 
Course: Data Structures and Algorithms
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

class Robot {
protected:
    std::string type, name;
    int x, y;
    bool isRandom, alive;
    int lives, shells;
    bool tracked = false;

public:
    Robot(std::string t, std::string n, std::string xStr, std::string yStr);
    virtual ~Robot();

    virtual void takeTurn(std::vector<std::vector<char>>&, std::vector<Robot*>&, std::ofstream& log) = 0;
    virtual void think(std::ofstream& log) = 0;
    virtual bool look(int dx, int dy, const std::vector<std::vector<char>>&, std::ofstream& log) = 0;
    virtual void fire(int dx, int dy, std::vector<std::vector<char>>&, std::vector<Robot*>&, std::ofstream& log) = 0;
    virtual void move(std::vector<std::vector<char>>&, std::vector<Robot*>&, std::ofstream& log) = 0;

    std::string getName() const;
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    bool isRandomPosition() const;
    bool isAlive() const;

    void kill(std::vector<std::vector<char>>& battlefield, std::ofstream& log);
    void respawn(std::vector<std::vector<char>>& battlefield, int rows, int cols, std::ofstream& log);
    
    bool canRespawn() const;

    void setTracked(bool status) { tracked = status; }
    bool isTracked() const { return tracked; }
};

#endif
