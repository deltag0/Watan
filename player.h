#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>

#include "board.h"
#include "criterion.h"


enum class Resources;
class Game_Controller;

enum class Dice {
    LOADED,
    FAIR
};


struct Player {
    // student color
    char color;
    std::string name;

    // resources
    int points = 0;
    int caffeine_count = 0;
    int lab_count = 0;
    int lecture_count = 0;
    int study_count = 0;
    int tutorial_count = 0;

    Dice die;
    // could make these dictionaries
    std::unordered_set<int> owned_criterions;
    std::unordered_set<int> owned_goal;

    bool won() const;
    int &find_resources(Resources ressource);

    // returns true if player owns goal
    bool owns_goal(const int pos) const;

    // returns true if player owns criterion
    bool owns_criterion(const int pos) const;

    private:
        Player(char color, std::string name);

        friend class Game_Controller;

};

// override operator to display status of player
std::ostream &operator<<(std::ostream &out, Player player);

#endif
