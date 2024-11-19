#ifndef CRITERION_H
#define CRITERION_H

#include <string>
#include "board.h"

#define MAX_CRITERION 54

class Tile;

// 54 criterions on one board
class Criterion {
    int level;
    Tile *tile;

    public:
        Criterion(int pos);
        ~Criterion() = default;

        Tile *get_tile();
        void set_tile(Tile *t);
};


#endif