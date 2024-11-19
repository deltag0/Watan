#ifndef CRITERION_H
#define CRITERION_H

#include <string>
#include "tile.h"
#include "asset.h"

#define MAX_CRITERION 54

class Tile;
class Asset;

// 54 criteria on one board
class Criterion : public Asset {
    int level = 0;
    Tile *tile;

    public:
        Criterion(int pos);
        ~Criterion() = default;

        Tile *get_tile();
        void set_tile(Tile *t);
};


#endif

