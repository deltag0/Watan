#include "player.h"

Player::Player(char color): color{color} {}

bool Player::won() {
    if (points == 10) return true;

    return false;
}