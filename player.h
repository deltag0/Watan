#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "board.h"
#include "criterion.h"
#include "observer.h"

#define NUM_PLAYERS 4
enum class Resources;
class Game_Controller;

enum class Dice {
    LOADED,
    FAIR
};

// Player contains all information for a human player
// Can only be constructed and modified by Game_Controller,
// Information in player is espacially used for finding valid actions for Board
// and outputting information by Game_Controller.
// Concrete Observer class
class Player : public Observer {
   public:
    // student identifier information
    char color;
    std::string name;
    int idx;

    // resources count
    int points = 0;
    int caffeine_count = 0;
    int lab_count = 0;
    int lecture_count = 0;
    int study_count = 0;
    int tutorial_count = 0;

    // type of die
    Dice die;

    // owned criterions and goals
    std::unordered_set<int> owned_criterions;
    std::unordered_set<int> owned_goal;

    // returns true if player won
    bool won() const;

    // returns the number of resources of type ressource
    int &find_resources(Resources ressource);

    // returns true if player owns goal
    bool owns_goal(const int pos) const;

    // returns true if player owns criterion
    bool owns_criterion(const int pos) const;

    // notifies player to output its status
    void notify() override;

   private:
    Player(char color, std::string name, int idx);

    friend class Game_Controller;
};

// override operator to display status of player
std::ostream &operator<<(std::ostream &out, Player player);

#endif
