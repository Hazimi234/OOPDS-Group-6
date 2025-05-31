/**********|**********|**********|
Program: Robot.cpp  
Course: Data Structures and Algorithms
Trimester: 2510
Name: Alif Akmal Bin Abdul Halim || Brian Ng Zheng Yang || Meor Hazimi Bin Meor Mohammad Fared || Yen Ming Jun
ID: 242UC244L7 || 242UC244RD || 242UC244PU || 243UC246NQ
Lecture Section: TC3L
Tutorial Section: T11L
Email: alif.akmal.abdul@student.mmu.edu.my || brian.ng.zheng@student.mmu.edu.my || meor.hazimi.meor@student.mmu.edu.my || yen.ming.jun@student.mmu.edu.my
Phone: +60 18-355-5944|| +60 17-779 3199 || +60 19-752 1755 ||+60 11-5372 6266
**********|**********|**********/

#include "Robot.h"
#include <iostream>
#include <cstdlib> 
#include <fstream>


using namespace std;

Robot::Robot(string t, string n, string xStr, string yStr)
    : type(t), name(n),
      alive(true), lives(3), shells(10)
{
    if (xStr == "random") {
        x = -1;
    } else {
        x = stoi(xStr);
    }

    if (yStr == "random") {
        y = -1;
    } else {
        y = stoi(yStr);
    }

    isRandom = (x == -1 || y == -1);
}


string Robot::getName() const { return name; }
int Robot::getX() const { return x; }
int Robot::getY() const { return y; }

void Robot::setShells(int s) {
    shells = s;
}

int Robot::getShells() const {
    return shells;
}


void Robot::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
    isRandom = false;
}

bool Robot::isRandomPosition() const {
    return isRandom;
}

bool Robot::isAlive() const {
    return alive;
}

void Robot::kill(vector<vector<char>>& battlefield, ofstream& log) {
    alive = false;
    lives--;
    battlefield[x][y] = '-';
    if (lives <= 0) {
        cout << name << " has been destroyed!\n";
        log << name << " has been destroyed!\n";
    } else {
        cout << name << " has lost a life! Remaining lives: " << lives << "\n";
        log << name << " has lost a life! Remaining lives: " << lives << "\n";
    }
}

bool Robot::canRespawn() const {
    return lives > 0;
}

void Robot::respawn(vector<vector<char>>& battlefield, int rows, int cols, ofstream& log) {
    int newX, newY;
    do {
        newX = rand() % rows;
        newY = rand() % cols;
    } while (battlefield[newX][newY] != '-');

    x = newX;
    y = newY;
    alive = true;
    battlefield[x][y] = name[0];
    cout << name << " has respawned at (" << x << "," << y << ")!\n";
}

Robot::~Robot() {}
