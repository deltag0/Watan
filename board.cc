#include "board.h"
#include "tiles.h"

Board::Board(std::vector<Tile *>tiles): tiles(tiles) {}

const std::vector<Tile *> &Board::get_tiles() const{
    return tiles;
}
