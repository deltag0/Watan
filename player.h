#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "board.h"
#include "criterion.h"

enum class Dice {
    LOADED,
    FAIR
};

struct Player {
    char color;

    int points;
    int caffeine_count;
    int lab_count;
    int lecture_count;
    int study_count;
    int tutorial;

    Dice die;
    std::vector<Board::Tile::Criterion *> owned_criterions;
    std::vector<Board::Tile::Goal *> owned_goal;

};

#endif