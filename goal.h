#ifndef GOAL_H
#define GOAL_H

#include <string>
#include "tile.h"
#include "asset.h"

#define MAX_GOAL 72

class Tile;
class Asset;

// Class for all goals on the board
class Goal : public Asset {  

    public:
        Goal(int pos);
        ~Goal() = default;
};


#endif
