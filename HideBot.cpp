#include "HideBot.h"
#include <cstdlib>
#include <ctime>

HideBot::HideBot(string name, int x, int y)
    : Robot(name, x, y), hidesRemaining(3), isHidden(false), hideTimer(0), hideDuration(1) {}

void HideBot::performTurn(const vector<Robot*>&) {
    cout << name << " is thinking..." << endl;

    if (isHidden) {
        if (hideTimer > 0) {
            cout << name << " is currently hidden. " << hideTimer << " turn(s) remaining." << endl;
            hideTimer--;
            if (hideTimer == 0) {
                unhide();
            }
        } else {
            // Shouldn’t happen, but safety check
            unhide();
        }
        return; // skip rest of turn
    }

    if (hidesRemaining > 0) {
        hide();
    } else {
        cout << name << " is exposed and has no hides left." << endl;
    }
}

void HideBot::takeDamage() {
    if (!isHidden) {
        isDestroyed = true;
        cout << name << " was destroyed!" << endl;
    } else {
        cout << name << " is hidden and avoided damage." << endl;
    }
}

bool HideBot::isHit() {
    return !isHidden;
}

void HideBot::hide() {
    if (hidesRemaining > 0 && !isHidden) {
        isHidden = true;
        hideTimer = hideDuration;
        hidesRemaining--;
        cout << name << " is hiding. Remaining hides: " << hidesRemaining << endl;
    }
}

void HideBot::unhide() {
    isHidden = false;
    hideTimer = 0;
    cout << name << " is no longer hidden." << endl;
}

void HideBot::displayStatus() const {
    Robot::displayStatus();
    cout << "Hidden: " << (isHidden ? "Yes" : "No") << ", Hides left: " << hidesRemaining << endl;
}

bool HideBot::getIsHidden() const { return isHidden; }
int HideBot::getHidesRemaining() const { return hidesRemaining; }
int HideBot::getHideTimer() const { return hideTimer; }