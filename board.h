#ifndef BOARD_H
#define BOARD_H

// probably fix something with headers
#include <string>
#include <vector>
#include <memory>

#include "tile.h"
#include "criterion.h"
#include "goal.h"
#include "player.h"

class Tile;
class Player;
class Goal;
class Criterion;

#define CORNERS 6
#define MAX_TILES 19

// Main board class (Model)
// Owns memory for ALL Tiles, Goals and Criterions
// Board is used to determine valid operations on the board and
// get data from the board 
class Board {
    public:
        Board(int seed = 0, bool is_seed = false, std::string filename = "", bool load = false);

        // getters
        const std::vector<std::unique_ptr<Tile>> &get_tiles() const;
        const std::vector<std::unique_ptr<Goal>> &get_goals() const;
        const std::vector<std::unique_ptr<Criterion>> &get_criteria() const;

        // gets the board in file filename at line line_num
        void get_board(const std::string &filename, int line_num);

        // returns a pointer to the tile with the goose
        const Tile *get_goose() const;

        // sets the Tile tile with the goose
        void set_goose(Tile *tile);

        // returns true if player can achieve goal at pos
        bool can_achieve(int pos, Player player) const;

        // returns true if player can complete the criterion at pos
        bool can_complete(const int pos, const bool sot, Player &player) const;
        

    private:
        std::vector<std::unique_ptr<Goal>> all_goals;
        std::vector<std::unique_ptr<Criterion>>all_criteria;
        std::vector<std::unique_ptr<Tile>> tiles;
        Tile *goose_tile;

        // Initialize tiles
        void initialize_tiles(int seed = 0, bool with_seed = false);

        // Attach criterions to all tiles 
        void link_criteria();

        // attach goals to all tiles
        void link_goals();

        // helper functions for can_achieve() for different positions of goals
        bool check_goal_0(Tile *tile, Player &player) const;
        bool check_goal_1(Tile *tile, Player &player) const;
        bool check_goal_2(Tile *tile, Player &player) const;
        bool check_goal_3(Tile *tile, Player &player) const;
        bool check_goal_4(Tile *tile, Player &player) const;
        bool check_goal_5(Tile *tile, Player &player) const;

        // helper functions for can_complete()
        bool check_complete_0(const int pos, const bool sot, Player &player) const;
        bool check_complete_1(const int pos, const bool sot, Player &player) const;
        bool check_complete_2(const int pos, const bool sot, Player &player) const;
        bool check_complete_3(const int pos, const bool sot, Player &player) const;
        bool check_complete_4(const int pos, const bool sot, Player &player) const;
        bool check_complete_5(const int pos, const bool sot, Player &player) const;
};

#define MAX_TILES 19
#define MAX_RESOURCE_LENGTH 8

// Available resources
enum class Resources {
    CAFFEINE,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX
};


// convert resources to other data types
std::string ResourceToString(Resources resource);

Resources StringToResource(const std::string &resource);

int ResourceToNum(Resources resource);

Resources NumToResource(int num);

#endif
