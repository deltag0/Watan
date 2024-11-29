#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "board.h"

class Board;
enum class Resources;
class Goal;
class Criterion;

// Main Tiles class
// Includes the resource, the position, the die value, 
// criterion, and goals
class Tile {
    public:
        bool has_goose = false;

        // gets tile position
        int get_pos() const;

        // gets tile roll_value
        int get_roll_val() const;

        // get criterions
        const std::vector<Criterion *> &get_criteria() const;

        //get goals
        const std::vector<Goal *> &get_goals() const;

        // get tile resource
        Resources get_resource() const;

        const Tile* get_bot() const;
        const Tile* get_top() const;
        const Tile* get_bot_left() const;
        const Tile* get_top_left() const;
        const Tile* get_top_right() const;
        const Tile* get_bot_right() const;

        // functions for print
        std::string display_resource() const;
        std::string display_roll_val() const;
        std::string display_goose() const;

    private:
        Tile(Resources r, int pos, int roll_value, Board *board);
        Board *board;
        Resources resource;
        int pos;
        int roll_value;
        std::vector<Goal *> goals;
        std::vector<Criterion *> criteria;

        friend class Board;
};

#endif
