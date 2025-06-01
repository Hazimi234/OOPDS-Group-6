#include "JumpBot.h"
#include "GenericRobot.h"
#include <cstdlib>
#include <ctime>

JumpBot::JumpBot() : jumpsRemaining(3) {}

void JumpBot::activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield,
                       std::ostream& log, const std::vector<Robot*>& robots) {
    if (jumpsRemaining <= 0 || !robot->isAlive()) {
        log << robot->getName() << " has no jumps left or is dead.\n";
        std::cout << robot->getName() << " has no jumps left or is dead.\n";
        robot->checkAndResetIfNoUpgrades();
        return;
    }

    int rows = battlefield.size();
    int cols = battlefield[0].size();

    int newX, newY;
    do {
        newX = std::rand() % rows;
        newY = std::rand() % cols;
    } while (battlefield[newX][newY] != '-'); // Find an empty cell

    // Clear the old position
    battlefield[robot->getX()][robot->getY()] = '-';

    // Update position
    robot->setPosition(newX, newY);
    battlefield[newX][newY] = robot->getName()[0];
    --jumpsRemaining;

    log << robot->getName() << " jumped to (" << newX << "," << newY << "). "
        << "Jumps remaining: " << jumpsRemaining << "\n";
    std::cout << robot->getName() << " jumped to (" << newX << "," << newY << "). "
              << "Jumps remaining: " << jumpsRemaining << "\n";
}

bool JumpBot::isJumpBot() const{
    return true;
}
