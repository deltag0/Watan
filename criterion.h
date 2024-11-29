#ifndef CRITERION_H
#define CRITERION_H

#include <string>
#include "tile.h"
#include "asset.h"

#define MAX_CRITERION 54

class Tile;
class Asset;

// Buildings that generate resources for players
class Criterion : public Asset {
    int level = 0;

    public:
        Criterion(int pos);
        ~Criterion() = default;

        // increases a level if a player improves it
        void increase_level();
        
        // need this function for loading board
        void set_level(int l);
        int get_level() const;


        // returns false if the Criterion is owned by player or if the Criterion is not owned yet
        bool in_the_way(const Player *player) const;
};

char level_to_building(int level);

#endif
