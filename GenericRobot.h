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
