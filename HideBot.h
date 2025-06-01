#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "Ability.h"
#include "GenericRobot.h"

class HideBot : public Ability {
private:
    int usesRemaining = 3;

public:
    bool tryHide(GenericRobot* robot, std::ostream& log); // attempt to hide when targeted
    bool isHideBot() const override { return true; }
    int getUsesRemaining() const { return usesRemaining; }
    void activate(GenericRobot* robot, std::vector<std::vector<char>>& battlefield, std::ostream& log, const std::vector<Robot*>& /*robots*/) override;

};

#endif
