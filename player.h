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

    // ressources
    int points;
    int caffeine_count;
    int lab_count;
    int lecture_count;
    int study_count;
    int tutorial_count;

    Dice die;
    std::vector<Board::Tile::Criterion *> owned_criterions;
    std::vector<Board::Tile::Goal *> owned_goal;
    Player(char color);

    bool won();
};

// override operator to display status of player
std::ostream &operator<<(std::ostream &out, Player player) {
    out << player.color << " has " << player.points << " victory points, "
    << player.caffeine_count << " caffeines, " << player.lab_count << " labs, "
    << player.lecture_count << " lectures, " << player.tutorial_count << " tutorials, "
    << " and " << player.study_count << " studies.";

    return out;
}


#endif