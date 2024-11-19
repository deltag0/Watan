#include "tile.h"


// criteria and goals initialized with placeholder values
Tile::Tile(Resources r, int pos, int roll_value, Board *board)
: board{board}, resource{r}, pos{pos}, roll_value{roll_value}, goals(6, nullptr), criteria(6, nullptr) {}

int Tile::get_pos() const {return pos;}

int Tile::get_roll_val() const {return roll_value;}

Tile* Tile::get_under() const {
    if (pos == 13 || pos == 16 || pos == 18 || pos == 17 || pos == 15) return nullptr;

    if (pos == 0) return board->tiles[4];

    return board->tiles[pos + 5];
}

Tile* Tile::get_top() const {
    if (pos == 3 || pos == 1 || pos == 0 || pos == 2 || pos == 5) return nullptr;

    if (pos == 4 || pos == 18) return board->tiles[pos - 4];


    return board->tiles[pos - 5];
}

Tile* Tile::get_bot_left() const {
    if (pos == 3 || pos == 8 || pos == 13 || pos == 16 || pos == 18) return nullptr;

    if (pos == 0 || pos == 17) return board->tiles[pos + 1];

    return board->tiles[pos + 2];
}

Tile* Tile::get_top_left() const {
    if (pos == 0 || pos == 1 || pos == 3 || pos == 8 || pos == 13) return nullptr;

    if (pos == 2 || pos == 18) return board->tiles[pos - 2];

    return board->tiles[pos - 3];
}

Tile* Tile::get_top_right() const {
    if (pos == 0 || pos == 2 || pos == 5 || pos == 10 || pos == 15) return nullptr;

    if (pos == 1 || pos == 18) return board->tiles[pos - 1];
    
    return board->tiles[pos - 2];
}

Tile* Tile::get_bot_right() const {
    if (pos == 17 || pos == 18 || pos == 5 || pos == 10 || pos == 15) return nullptr;

    if (pos == 16 || pos == 0) return board->tiles[pos + 2];

    return board->tiles[pos + 3];
}
