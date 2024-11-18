#ifndef BOARD_H
#define BOARD_H

// probably fix something with headers
#include <string>
#include <vector>

#include "goal.h"


// Main board class
// Includes Tiles, Goose placement, 
class Board {
    public:
        class Tile;
        Board(int seed = 0, bool is_seed = false);
        const std::vector<Tile *> &get_tiles() const;
        std::vector<Tile *> initialize_tiles(std::vector<Criterion *> &criterias, std::vector<Goal *> &goals, int seed = 0, bool with_seed = false);

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
    public:
        // // Board Assets abstract class
        // super class for Criterion and Goal
        class Asset {
            protected:
                int pos;
                Board::Tile *tile;
                std::string display; // value displayed on the board for the asset
                bool is_captured = false;

            public:
                Asset(int pos): pos{pos}, display{std::to_string(pos)} {};
                virtual ~Asset() = 0;
                int get_pos();
                std::string get_display();
        };
        class Criterion;
        class Goal;
        bool has_goose = false;

        // gets tile position
        int get_pos() const;

        // gets tile roll_value
        int get_roll_val() const;

        Tile* get_under() const;
        Tile* get_top() const;
        Tile* get_bott_left() const;
        Tile* get_top_left() const;
        Tile* get_top_right() const;
        Tile* get_bott_right() const;


    private:
        Tile(Ressources r, int pos, int roll_value, Board *board);
        Board *board;
        Ressources ressource;
        int pos;
        int roll_value;
        std::vector<Goal *> goals;
        std::vector<Criterion *> criterias;

        friend class Board;
};

// 54 criterions on one board
class Board::Tile::Criterion: public Board::Tile::Asset {
    friend class Board::Tile;
    int level;

    public:
        Criterion(int pos);
        ~Criterion();

        Tile *get_tile();
        void set_tile(Board::Tile *t);
};

// convert class name to string valued name
std::string RessourceToString(Ressources ressource);

#endif