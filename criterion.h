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

        void set_tile(Tile *t);
        Tile *get_tile() const;

        void increase_level();
        int get_level() const;

        // returns false if the Criterion is owned by player or if the Criterion is not owned yet
        bool in_the_way(const Player *player) const;
};


#endif

