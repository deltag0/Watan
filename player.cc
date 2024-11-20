#include "player.h"

Player::Player(char color, std::string name): color{color}, name{name}, die{Dice::FAIR} {}

bool Player::won() const{
    if (points == 10) return true;

    return false;
}

bool Player::owns_goal(int pos) const {
    if (owned_goal.find(pos) != owned_goal.end()) return true;
    
    return false;
}

void Player::print() const {
    std::cout << name << " has " << points << " victory points, "
    << caffeine_count << " caffeines, " << lab_count << " labs, "
    << lecture_count << " lectures, " << tutorial_count << " tutorials, "
    << "and " << study_count << " studies." << '\n';
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
