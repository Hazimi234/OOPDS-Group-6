#ifndef HIDEBOT_H
#define HIDEBOT_H

#include "Robot.h"

class HideBot : public Robot {
private:
    int hidesRemaining;
    bool isHidden;
    int hideTimer;
    int hideDuration;

public:
    HideBot(string name, int x, int y);
    void performTurn(const vector<Robot*>& robots) override;
    void takeDamage() override;
    bool isHit() override;
    void hide();
    void unhide();
    void displayStatus() const override;

    bool getIsHidden() const;
    int getHidesRemaining() const;
    int getHideTimer() const;
};

#endif