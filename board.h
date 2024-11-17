#ifndef BOARD_H
#define BOARD_H

// probably fix something with headers
#include <string>
#include <vector>

#include "criterion.h"
#include "board.h"
#include "goal.h"

// Main board class
// Includes Tiles, Goose placement, 
class Board {
    public:
        class Tile;
        Board();
        const std::vector<Tile *> &get_tiles() const;
        std::vector<Board::Tile *> initialize_tiles(std::vector<Criterion *> &criterias, std::vector<Goal *> &goals, int seed = 0, bool with_seed = false);

    private:
        std::vector<Goal *> all_goals;
        std::vector<Criterion *>all_criterias;
        std::vector<Tile *> tiles;
        Tile *goose_tile;

        // Attach criterions to all tiles 
        void link_criteria();

        // attach goals to all tiles
        void link_goals();
};

#define MAX_TILES 19

// Available ressources
enum class Ressources {
    CAFFEINE,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX
};

// Main Tiles class
// Includes the ressource, the position, the die value, 
// criterion, and goals
class Board::Tile {
    friend class Board;
    Ressources ressource;
    int pos;
    int roll_value;
    std::vector<Goal *> goals;
    Tile(Ressources r, int pos, int roll_value);

    public:
        // class Asset {
        //     int display;  // value displayed before a player takes contron of the asset
        //     std::string player_name;
        //     bool is_captured = false;

        //     public:
        //         Asset(int display);
        //         virtual ~Asset() = 0;
        // };
        // Sets up all fields for the game except for the criterias and goals
        // which are set up seperately

        std::vector<Criterion *> criterias; // for testing (should be private)

        // gets tile position
        int get_pos() const;

        // gets tile roll_value
        int get_roll_val() const;
};

// convert class name to string valued name
std::string RessourceToString(Ressources ressource);

#endif