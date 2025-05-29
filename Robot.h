#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>

using namespace std;

class Robot {
protected:
    string type, name;
    int x, y;
    bool isRandom, alive;
    int lives, shells;

public:
    Robot(string t, string n, string xStr, string yStr);
    virtual ~Robot();

    virtual void takeTurn(vector<vector<char>>&, vector<Robot*>&) = 0;
    virtual void think() = 0;
    virtual bool look(int dx, int dy, const vector<vector<char>>&) = 0;
    virtual void fire(int dx, int dy, vector<vector<char>>&, vector<Robot*>&) = 0;
    virtual void move(vector<vector<char>>&, vector<Robot*>&) = 0;

    string getName() const;
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
    bool isRandomPosition() const;
    bool isAlive() const;
    void kill(vector<vector<char>>&);
    bool canRespawn() const;
    void respawn(vector<vector<char>>&, int rows, int cols);
};

#endif
