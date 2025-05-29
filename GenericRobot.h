#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include <iostream>
#include <vector>
#include <string>
#include "Robot.h"

using namespace std;

class GenericRobot : public Robot {
public:
    GenericRobot(string t, string n, string xStr, string yStr);

    void think() override;
    bool look(int dx, int dy, const vector<vector<char>>& battlefield) override;
    void fire(int dx, int dy, vector<vector<char>>& battlefield,
              vector<Robot*>& robots) override;
    void move(vector<vector<char>>& battlefield);
    void move(vector<vector<char>>& battlefield, vector<Robot*>& robots) override;
    void takeTurn(vector<vector<char>>& battlefield, vector<Robot*>& robots) override;
};

#endif // GENERICROBOT_H
