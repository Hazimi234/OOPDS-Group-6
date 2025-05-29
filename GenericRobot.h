#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include <iostream>
#include <vector>
#include <string>
#include "Robot.h"

class GenericRobot : public Robot {
public:
    GenericRobot(std::string t, std::string n, std::string xStr, std::string yStr);

    void think() override;
    bool look(int dx, int dy, const std::vector<std::vector<char>>& battlefield) override;
    void fire(int dx, int dy, std::vector<std::vector<char>>& battlefield,
              std::vector<Robot*>& robots) override;
    void move(std::vector<std::vector<char>>& battlefield);
    void move(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots) override;
    void takeTurn(std::vector<std::vector<char>>& battlefield, std::vector<Robot*>& robots) override;
};

#endif // GENERICROBOT_H
