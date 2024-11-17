#include <string>

#include "tiles.h"
#include "stdexcept"

// returns: string value of ressource
std::string RessourceToString(Ressources ressource) {
    switch (ressource) {
        case Ressources::CAFFEINE:
            return "CAFFEINE";
        case Ressources::LAB:
            return "LAB";
        case Ressources::LECTURE:
            return "LECTURE";
        case Ressources::STUDY:
            return "STUDY";
        case Ressources::TUTORIAL:
            return "TUTORIAL";
        case Ressources::NETFLIX:
            return "NETFLIX";
        default:
            throw std::invalid_argument("Invalid Ressources value");
    }
}

// criterias and goals initialized with placeholder values
Tile::Tile(Ressources r, int pos, int roll_value)
: ressource{r}, pos{pos}, roll_value{roll_value}, criterias(4, nullptr), goals(4, nullptr) {}

int Tile::get_pos() const {return pos;}

int Tile::get_roll_val() const {return roll_value;}