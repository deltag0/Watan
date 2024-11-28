#ifndef BOARD_H
#define BOARD_H

// probably fix something with headers
#include <string>
#include <vector>

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

// Main board class
// Includes Tiles, Goose placement, 
class Board {
    public:
        Board(int seed = 0, bool is_seed = false, std::string filename = "", bool load = false);
        const std::vector<Tile *> &get_tiles() const;
        const std::vector<Goal *> &get_goals() const;
        const std::vector<Criterion *> &get_criteria() const;
        
        void initialize_tiles(int seed = 0, bool with_seed = false);
        void get_board(const std::string &filename, int line_num);

        bool can_achieve(int pos, Player player) const;
        
        // helper functions for can_achieve() for different positions of goals
        bool check_goal_0(Tile *tile, Player player) const;
        bool check_goal_1(Tile *tile, Player player) const;
        bool check_goal_2(Tile *tile, Player player) const;
        bool check_goal_3(Tile *tile, Player player) const;
        bool check_goal_4(Tile *tile, Player player) const;
        bool check_goal_5(Tile *tile, Player player) const;
        
        const Tile *get_goose() const;
        void set_goose(Tile *tile);

    private:
        std::vector<Goal *> all_goals;
        std::vector<Criterion *>all_criteria;
        std::vector<Tile *> tiles;
        Tile *goose_tile;

        // Attach criterions to all tiles 
        void link_criteria();

        // attach goals to all tiles
        void link_goals();
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


// convert class name to string valued name
std::string ResourceToString(Resources resource);

Resources StringToResource(const std::string &resource);

int ResourceToNum(Resources resource);

Resources NumToResource(int num);

#endif
