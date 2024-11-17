#ifndef TILES_H
#define TILES_H

#include <string>
#include <vector>

#include "criterion.h"
#include "goal.h"

#define MAX_TILES 19

// Available ressources
enum class Ressources {
    CAFFEINE,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX
};

// Main Tiles class
// Includes the ressource, the position, the die value, 
// criterion, and goals
class Tile {
    Ressources ressource;
    int pos;
    int roll_value;
    std::vector<Criterion *> criterias;
    std::vector<Goal *> goals;

    public:
        // Sets up all fields for the game except for the criterias and goals
        // which are set up seperately
        Tile(Ressources r, int pos, int roll_value);

        // gets tile position
        int get_pos() const;

        // gets tile roll_value
        int get_roll_val() const;
};

// convert class name to string valued name
std::string RessourceToString(Ressources ressource);

#endif