#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "tiles.h"

// Main board class
// Includes Tiles, Goose placement, 
class Board {
    std::vector<Tile *> tiles;
    Tile *goose_tile;

    public:
        Board(std::vector<Tile *>tiles);
        const std::vector<Tile *> &get_tiles() const;
};


#endif