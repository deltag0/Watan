#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "board.h"
#include "criterion.h"

#define NUM_PLAYERS 4
#define MIN_ROLL 2
#define MAX_ROLL 12

enum class Resources;

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
    int &find_resources(Resources resource);

    // returns true if player owns criterion
    bool owns_criterion(const int pos) const;

    // returns true if player owns goal
    bool owns_goal(int pos) const;

    friend class Game_Controller;

   private:
    Player(char color, std::string name);
};

// print status of player
std::ostream &operator<<(std::ostream &out, Player player);

#endif
