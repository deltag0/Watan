#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>

#include "board.h"
#include "criterion.h"

enum class Dice {
    LOADED,
    FAIR
};

struct Player {
    // student color
    char color;

    // resources
    int points;
    int caffeine_count;
    int lab_count;
    int lecture_count;
    int study_count;
    int tutorial_count;

    Dice die;
    std::vector<Criterion *> owned_criterions;
    std::vector<Goal *> owned_goal;
    Player(char color);

    bool won();
};

// override operator to display status of player
std::ostream &operator<<(std::ostream &out, Player player);

#endif
