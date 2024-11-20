#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <string>

#include "board.h"
#include "criterion.h"

#define NUM_PLAYERS 4

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
    std::vector<Criterion *> owned_criterions;
    std::vector<Goal *> owned_goal;
    Player(char color, std::string name);

    bool won() const;
    int &find_resources(Resources ressource);
};

// override operator to display status of player
std::ostream &operator<<(std::ostream &out, Player player);

#endif
