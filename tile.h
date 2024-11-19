#ifndef TILE_H
#define TILE_H

#include <string>
#include "board.h"

class Board;
enum class Ressources;
class Goal;
class Criterion;

// Main Tiles class
// Includes the ressource, the position, the die value, 
// criterion, and goals
class Tile {
    public:
        // // Board Assets abstract class
        // super class for Criterion and Goal
        class Asset {
            protected:
                int pos;
                Tile *tile;
                std::string display; // value displayed on the board for the asset
                bool is_captured = false;

            public:
                Asset(int pos): pos{pos}, display{std::to_string(pos)} {};
                virtual ~Asset() = 0;
                int get_pos();
                std::string get_display();
        };
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

        // could find a way to get rid of this
        friend class Board;
};

#endif