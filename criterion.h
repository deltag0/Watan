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

    public:
        Criterion(int pos);
        ~Criterion() = default;

        // could make Board a friend of criterion, but it's alright
        void set_tile(Tile *t);
        Tile *get_tile();
};


#endif

