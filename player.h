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

class Player {
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
    Player(char color, std::string name);

   public:
    bool won() const;
<<<<<<< HEAD
    int &find_resources(Resources ressource);

    // returns true if player owns goal
    bool owns_goal(const int pos) const;

    // returns true if player owns criterion
    bool owns_criterion(const int pos) const;

=======
    int &find_resources(Resources resource);
    // returns true if player owns goal
    bool owns_goal(int pos) const;

    // print status of player
    void print() const;

    friend class Game_Controller;
>>>>>>> 4d56ff2ca5a46397e7648d2cc4be8c5b94b9a823
};

#endif
