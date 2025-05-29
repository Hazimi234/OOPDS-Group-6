#include "Robot.h"
#include <iostream>
#include <cstdlib>

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

void Robot::kill(vector<vector<char>>& battlefield) {
    alive = false;
    lives--;
    battlefield[x][y] = '-';
    if (lives <= 0) {
        cout << name << " has been destroyed!\n";
    } else {
        cout << name << " has lost a life! Remaining lives: " << lives << "\n";
    }
}

bool Robot::canRespawn() const {
    return lives > 0;
}

void Robot::respawn(vector<vector<char>>& battlefield, int rows, int cols) {
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
