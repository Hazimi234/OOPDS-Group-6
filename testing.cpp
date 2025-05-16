/***********|***********|***********|
Program: TC01.1234567.YourName.cpp  
Course: CCP6124 Object Oriented Programming and Data Structures
Trimester: 2510
Name: Your Name 
ID: YourStudentID 
Lecture Section: TCXX 
Tutorial Section: TTL 
Email: your@email.com 
Phone: 012-3456789 
***********|***********|***********/

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

// ==================== SECTION 1: BASE CLASSES ====================
class BattleField; // Forward declaration
// Add to BattleField class
void displayBattlefield() const {
    const int width = getWidth();
    const int height = getHeight();
    
    // Top border
    std::cout << "+";
    for (int x = 0; x < width; x++) std::cout << "-";
    std::cout << "+\n";

    for (int y = 0; y < height; y++) {
        std::cout << "|"; // Left border
        for (int x = 0; x < width; x++) {
            if (Robot* robot = getRobotAt(x, y)) {
                if (robot->isHidden()) {
                    std::cout << " "; // Hidden robots are invisible
                } else {
                    // Display first letter of robot's name
                    std::cout << robot->getName()[0];
                }
            } else {
                std::cout << " "; // Empty space
            }
        }
        std::cout << "|\n"; // Right border
    }

    // Bottom border
    std::cout << "+";
    for (int x = 0; x < width; x++) std::cout << "-";
    std::cout << "+\n";
}

// Modified runSimulation() in RobotWarSimulator
void runSimulation() {
    std::cout << "=== Starting Robot War Simulation ===\n";
    battlefield.displayBattlefield(); // Initial display
    
    while (currentStep < totalSteps && battlefield.getRobots().size() > 1) {
        currentStep++;
        std::cout << "\n=== Step " << currentStep << " ===\n";
        
        // Process each robot's turn
        auto robots = battlefield.getRobots(); // Make a copy to avoid iterator invalidation
        for (const auto& robot : robots) {
            if (!robot->isAlive()) continue;
            
            std::cout << "\n[" << robot->getName() << "'s turn]\n";
            std::cout << "Type: " << robot->getType() << "\n";
            std::cout << "Position: (" << robot->getPosition().first 
                      << "," << robot->getPosition().second << ")\n";
            
            robot->think(battlefield);
            robot->act(battlefield);
            
            battlefield.displayBattlefield(); // Show updated battlefield
            
            // Pause for player to see what happened
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
        }
        
        if (battlefield.getRobots().size() == 1) break;
    }
    
    // ... rest of the simulation end code ...
}

class Robot {
protected:
    int positionX;
    int positionY;
    std::string name;
    int lives = 3;
    bool hidden = false;
    
public:
    Robot(int x, int y, const std::string& name) 
        : positionX(x), positionY(y), name(name) {}
    virtual ~Robot() = default;
    
    virtual void think(BattleField& battlefield) = 0;
    virtual void act(BattleField& battlefield) = 0;
    
    std::string getName() const { return name; }
    std::pair<int, int> getPosition() const { return {positionX, positionY}; }
    bool isAlive() const { return lives > 0; }
    void takeDamage() { if (!hidden) lives--; }
    void setHidden(bool state) { hidden = state; }
    bool isHidden() const { return hidden; }
    virtual std::string getType() const { return "Generic"; }
};

class MovingRobot {
public:
    virtual ~MovingRobot() = default;
    virtual void move(BattleField& battlefield, int dx, int dy) = 0;
    virtual bool canJump() const { return false; }
    virtual bool canHide() const { return false; }
};

class ShootingRobot {
public:
    virtual ~ShootingRobot() = default;
    virtual void fire(BattleField& battlefield, int dx, int dy) = 0;
    virtual bool hasAmmo() const = 0;
    virtual int getAmmoCount() const = 0;
};

class SeeingRobot {
public:
    virtual ~SeeingRobot() = default;
    virtual void look(BattleField& battlefield, int dx, int dy) = 0;
    virtual bool canScout() const { return false; }
    virtual bool canTrack() const { return false; }
};

class ThinkingRobot {
public:
    virtual ~ThinkingRobot() = default;
    virtual void strategize(BattleField& battlefield) = 0;
};

// ==================== SECTION 2: BATTLEFIELD ====================
class BattleField {
private:
    int width;
    int height;
    std::vector<std::shared_ptr<Robot>> robots;
    std::map<std::string, std::pair<int, int>> trackedRobots;
    
public:
    BattleField(int w, int h) : width(w), height(h) {}
    
    bool isValidPosition(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
    
    Robot* getRobotAt(int x, int y) const {
        for (const auto& robot : robots) {
            auto [rx, ry] = robot->getPosition();
            if (rx == x && ry == y) {
                return robot.get();
            }
        }
        return nullptr;
    }
    
    void addRobot(std::shared_ptr<Robot> robot) {
        robots.push_back(robot);
    }
    
    void removeRobot(Robot* robot) {
        robots.erase(std::remove_if(robots.begin(), robots.end(), 
            [robot](const std::shared_ptr<Robot>& r) { 
                return r.get() == robot; 
            }), robots.end());
    }
    
    const std::vector<std::shared_ptr<Robot>>& getRobots() const {
        return robots;
    }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void trackRobot(const std::string& name, int x, int y) {
        trackedRobots[name] = {x, y};
    }
    
    std::pair<int, int> getTrackedPosition(const std::string& name) const {
        auto it = trackedRobots.find(name);
        if (it != trackedRobots.end()) {
            return it->second;
        }
        return {-1, -1};
    }
};

// ==================== SECTION 3: ROBOT IMPLEMENTATIONS ====================
class GenericRobot : public Robot, 
                    public MovingRobot, 
                    public ShootingRobot, 
                    public SeeingRobot, 
                    public ThinkingRobot {
protected:
    int ammo = 10;
    bool hasUpgraded[3] = {false}; // 0:Moving, 1:Shooting, 2:Seeing
    
public:
    GenericRobot(int x, int y, const std::string& name) 
        : Robot(x, y, name) {}
    
    std::string getType() const override { return "GenericRobot"; }

    // MovingRobot implementation
    void move(BattleField& battlefield, int dx, int dy) override {
        int newX = positionX + dx;
        int newY = positionY + dy;
        
        if (battlefield.isValidPosition(newX, newY) && 
            !battlefield.getRobotAt(newX, newY)) {
            positionX = newX;
            positionY = newY;
            std::cout << name << " moved to (" << positionX << "," << positionY << ")\n";
        }
    }
    
    // ShootingRobot implementation
    void fire(BattleField& battlefield, int dx, int dy) override {
        if (ammo <= 0) {
            std::cout << name << " has no ammo left!\n";
            return;
        }
        
        if (dx == 0 && dy == 0) {
            std::cout << name << " refuses to commit suicide!\n";
            return;
        }
        
        int targetX = positionX + dx;
        int targetY = positionY + dy;
        
        if (!battlefield.isValidPosition(targetX, targetY)) {
            std::cout << name << " fired at invalid position!\n";
            return;
        }
        
        ammo--;
        std::cout << name << " fired at (" << targetX << "," << targetY << "). ";
        std::cout << "Ammo left: " << ammo << "\n";
        
        // 70% chance to hit
        if ((rand() % 100) < 70) {
            if (Robot* target = battlefield.getRobotAt(targetX, targetY)) {
                std::cout << "Direct hit! " << target->getName() << " takes damage.\n";
                target->takeDamage();
                
                if (!target->isAlive()) {
                    std::cout << target->getName() << " was destroyed!\n";
                    battlefield.removeRobot(target);
                    considerUpgrade();
                }
            }
        } else {
            std::cout << "Shot missed!\n";
        }
        
        if (ammo == 0) {
            std::cout << name << " has no ammo left and self-destructs!\n";
            battlefield.removeRobot(this);
        }
    }
    
    bool hasAmmo() const override { return ammo > 0; }
    int getAmmoCount() const override { return ammo; }
    
    // SeeingRobot implementation
    void look(BattleField& battlefield, int dx, int dy) override {
        int lookX = positionX + dx;
        int lookY = positionY + dy;
        
        if (!battlefield.isValidPosition(lookX, lookY)) {
            std::cout << name << " sees nothing at (" << lookX << "," << lookY 
                      << ") - out of bounds\n";
            return;
        }
        
        if (Robot* robot = battlefield.getRobotAt(lookX, lookY)) {
            std::cout << name << " sees " << robot->getName() 
                      << " at (" << lookX << "," << lookY << ")\n";
        } else {
            std::cout << name << " sees nothing at (" << lookX << "," << lookY << ")\n";
        }
    }
    
    // ThinkingRobot implementation
    void strategize(BattleField& battlefield) override {
        // Simple random strategy for example
        int action = rand() % 3;
        
        switch (action) {
            case 0: {
                // Random move
                int dx = (rand() % 3) - 1; // -1, 0, or 1
                int dy = (rand() % 3) - 1;
                move(battlefield, dx, dy);
                break;
            }
            case 1: {
                // Random look
                int dx = (rand() % 3) - 1;
                int dy = (rand() % 3) - 1;
                look(battlefield, dx, dy);
                break;
            }
            case 2: {
                // Random fire if ammo available
                if (hasAmmo()) {
                    int dx = (rand() % 3) - 1;
                    int dy = (rand() % 3) - 1;
                    if (dx != 0 || dy != 0) { // Don't fire at self
                        fire(battlefield, dx, dy);
                    }
                }
                break;
            }
        }
    }
    
    // Robot implementation
    void think(BattleField& battlefield) override {
        strategize(battlefield);
    }
    
    void act(BattleField& battlefield) override {
        if (!isAlive()) return;
        
        strategize(battlefield);
    }
    
protected:
    void considerUpgrade() {
        for (int i = 0; i < 3; i++) {
            if (!hasUpgraded[i]) {
                hasUpgraded[i] = true;
                std::string upgradeType;
                switch (i) {
                    case 0: upgradeType = "Moving"; break;
                    case 1: upgradeType = "Shooting"; break;
                    case 2: upgradeType = "Seeing"; break;
                }
                std::cout << name << " earned an upgrade in " << upgradeType << "!\n";
                return;
            }
        }
    }
};

// ==================== SECTION 4: UPGRADED ROBOTS ====================
class HideBot : public GenericRobot {
private:
    int hideCharges = 3;
    
public:
    HideBot(int x, int y, const std::string& name) 
        : GenericRobot(x, y, name) {}
    
    std::string getType() const override { return "HideBot"; }
    bool canHide() const override { return true; }

    void think(BattleField& battlefield) override {
        if (hideCharges > 0 && (rand() % 100) < 30) {
            setHidden(true);
            hideCharges--;
            std::cout << getName() << " is now hidden! (" 
                      << hideCharges << " charges left)\n";
        } else {
            GenericRobot::think(battlefield);
        }
    }
    
    void act(BattleField& battlefield) override {
        if (!isAlive()) return;
        
        if (isHidden()) {
            std::cout << getName() << " remains hidden this turn\n";
            setHidden(false);
        } else {
            GenericRobot::act(battlefield);
        }
    }
};

class JumpBot : public GenericRobot {
private:
    int jumpCharges = 3;
    
public:
    JumpBot(int x, int y, const std::string& name) 
        : GenericRobot(x, y, name) {}
    
    std::string getType() const override { return "JumpBot"; }
    bool canJump() const override { return true; }

    void move(BattleField& battlefield, int dx, int dy) override {
        if (jumpCharges > 0 && (dx > 1 || dy > 1 || dx < -1 || dy < -1)) {
            // This is a jump
            jumpCharges--;
            int newX = positionX + dx;
            int newY = positionY + dy;
            
            if (battlefield.isValidPosition(newX, newY) && 
                !battlefield.getRobotAt(newX, newY)) {
                positionX = newX;
                positionY = newY;
                std::cout << getName() << " jumped to (" << positionX 
                          << "," << positionY << "). Charges left: " 
                          << jumpCharges << "\n";
            }
        } else {
            // Normal move
            GenericRobot::move(battlefield, dx, dy);
        }
    }
};

class LongShotBot : public GenericRobot {
public:
    LongShotBot(int x, int y, const std::string& name) 
        : GenericRobot(x, y, name) {}
    
    std::string getType() const override { return "LongShotBot"; }

    void fire(BattleField& battlefield, int dx, int dy) override {
        // Check if target is within 3 units distance
        if (abs(dx) + abs(dy) > 3) {
            std::cout << getName() << " - Target too far for shooting!\n";
            return;
        }
        GenericRobot::fire(battlefield, dx, dy);
    }
};

// ==================== SECTION 5: SIMULATION ====================
class SimulationInitializer {
public:
    int width;
    int height;
    int steps;
    int robotCount;
    std::vector<std::tuple<std::string, std::string, int, int>> robots;
    
    bool parseInitializationFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            if (line.find("M by N :") != std::string::npos) {
                std::istringstream iss(line.substr(line.find(":") + 1));
                iss >> width >> height;
            }
            else if (line.find("steps:") != std::string::npos) {
                steps = std::stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("robots:") != std::string::npos) {
                robotCount = std::stoi(line.substr(line.find(":") + 1));
            }
            else {
                std::istringstream iss(line);
                std::string type, name, xPos, yPos;
                iss >> type >> name >> xPos >> yPos;
                
                bool randomPos = (xPos == "random" || yPos == "random");
                int x = randomPos ? -1 : std::stoi(xPos);
                int y = randomPos ? -1 : std::stoi(yPos);
                
                robots.emplace_back(type, name, x, y);
            }
        }
        
        file.close();
        
        if (width <= 0 || height <= 0 || steps <= 0 || robotCount <= 0 || 
            static_cast<int>(robots.size()) != robotCount) {
            std::cerr << "Error: Invalid initialization file format" << std::endl;
            return false;
        }
        
        return true;
    }
};

class RobotWarSimulator {
private:
    BattleField battlefield;
    int totalSteps;
    int currentStep = 0;
    std::ofstream logFile;
    
public:
    RobotWarSimulator(int width, int height, int steps) 
        : battlefield(width, height), totalSteps(steps) {
        logFile.open("robot_war_log.txt");
    }
    
    ~RobotWarSimulator() {
        logFile.close();
    }
    
    void addRobot(std::shared_ptr<Robot> robot) {
        battlefield.addRobot(robot);
    }
    
    void runSimulation() {
        std::cout << "=== Starting Robot War Simulation ===\n";
        std::cout << "Battlefield: " << battlefield.getWidth() << "x" 
                  << battlefield.getHeight() << "\n";
        std::cout << "Total steps: " << totalSteps << "\n";
        std::cout << "Initial robots: " << battlefield.getRobots().size() << "\n\n";
        
        logFile << "=== Simulation Log ===\n";
        logFile << "Battlefield: " << battlefield.getWidth() << "x" 
                << battlefield.getHeight() << "\n";
        logFile << "Total steps: " << totalSteps << "\n";
        logFile << "Initial robots: " << battlefield.getRobots().size() << "\n\n";
        
        while (currentStep < totalSteps && battlefield.getRobots().size() > 1) {
            currentStep++;
            std::cout << "\n=== Step " << currentStep << " ===\n";
            logFile << "\n=== Step " << currentStep << " ===\n";
            
            for (const auto& robot : battlefield.getRobots()) {
                if (robot->isAlive()) {
                    std::cout << "\n[" << robot->getName() << "'s turn]\n";
                    logFile << "\n[" << robot->getName() << "'s turn]\n";
                    
                    robot->think(battlefield);
                    robot->act(battlefield);
                }
            }
            
            if (battlefield.getRobots().size() == 1) {
                std::cout << "\n=== Game Over ===\n";
                std::cout << battlefield.getRobots()[0]->getName() 
                          << " is the last robot standing!\n";
                logFile << "\n=== Game Over ===\n";
                logFile << battlefield.getRobots()[0]->getName() 
                        << " is the last robot standing!\n";
                break;
            }
        }
        
        if (currentStep >= totalSteps) {
            std::cout << "\n=== Simulation Ended ===\n";
            std::cout << "Maximum steps reached. " 
                      << battlefield.getRobots().size() << " robots remain.\n";
            logFile << "\n=== Simulation Ended ===\n";
            logFile << "Maximum steps reached. " 
                    << battlefield.getRobots().size() << " robots remain.\n";
        }
    }
};

// ==================== SECTION 6: MAIN FUNCTION ====================
int main() {
    std::srand(std::time(0));
    
    // Parse initialization file
    SimulationInitializer initializer;
    if (!initializer.parseInitializationFile("simulation_init.txt")) {
        return 1;
    }
    
    // Create battlefield and simulator
    RobotWarSimulator simulator(initializer.width, initializer.height, initializer.steps);
    
    // Create and add robots
    for (const auto& [type, name, x, y] : initializer.robots) {
        std::shared_ptr<Robot> robot;
        int actualX = (x == -1) ? rand() % initializer.width : x;
        int actualY = (y == -1) ? rand() % initializer.height : y;
        
        if (type == "GenericRobot") {
            robot = std::make_shared<GenericRobot>(actualX, actualY, name);
        } 
        else if (type == "HideBot") {
            robot = std::make_shared<HideBot>(actualX, actualY, name);
        }
        else if (type == "JumpBot") {
            robot = std::make_shared<JumpBot>(actualX, actualY, name);
        }
        else if (type == "LongShotBot") {
            robot = std::make_shared<LongShotBot>(actualX, actualY, name);
        }
        else {
            std::cerr << "Unknown robot type: " << type << std::endl;
            continue;
        }
        
        simulator.addRobot(robot);
    }
    
    // Run simulation
    simulator.runSimulation();
    
    return 0;
}