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
};

#endif
