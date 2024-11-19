#include "player.h"

Player::Player(char color): color{color} {}

bool Player::won() {
    if (points == 10) return true;

    return false;
}

std::ostream &operator<<(std::ostream &out, Player player) {
    out << player.color << " has " << player.points << " victory points, "
    << player.caffeine_count << " caffeines, " << player.lab_count << " labs, "
    << player.lecture_count << " lectures, " << player.tutorial_count << " tutorials, "
    << " and " << player.study_count << " studies.";

    return out;
}
