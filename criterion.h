#ifndef CRITERION_H
#define CRITERION_H

#include <string>
#include "board.h"

#define MAX_CRITERION 54

// 53 criterions on one board
class Board::Tile::Criterion: public Board::Tile::Asset {
    friend class Board::Tile;
    int level;

    // Set the parent tile as the tile with the smallest position
    Board::Tile *tile;

    public:
        Criterion(int pos);
        ~Criterion();

};


#endif