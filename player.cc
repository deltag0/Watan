#include "player.h"

Player::Player(char color, std::string name): color{color}, name{name}, die{Dice::FAIR} {}

bool Player::won() const{
    if (points == 10) return true;

    return false;
}

std::ostream &operator<<(std::ostream &out, Player player) {
    out << player.name << " has " << player.points << " victory points, "
    << player.caffeine_count << " caffeines, " << player.lab_count << " labs, "
    << player.lecture_count << " lectures, " << player.tutorial_count << " tutorials, "
    << "and " << player.study_count << " studies." << '\n';

    return out;
}

int &Player::find_resources(Resources ressource) {
    switch (ressource) {
        case Resources::CAFFEINE:
            return caffeine_count;
        case Resources::LAB:
            return lab_count;
        case Resources::LECTURE:
            return lecture_count;
        case Resources::STUDY:
            return study_count;
        case Resources::TUTORIAL:
            return tutorial_count;
        default:
            throw std::invalid_argument("Invalid resource type");
    }
}
