#ifndef GOAL_H
#define GOAL_H

#include <string>
#include "tile.h"
#include "asset.h"

#define MAX_GOAL 72

class Tile;
class Asset;

// 72 goals on one board
class Goal : public Asset {  

    public:
        Goal(int pos);
        ~Goal() = default;
        
        Tile *get_tile();
        void set_tile(Tile *t);

};


#endif
