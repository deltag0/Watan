#ifndef BOARD_H
#define BOARD_H

// probably fix something with headers
#include <string>
#include <vector>

#include "tile.h"
#include "criterion.h"
#include "goal.h"


// Main board class
// Includes Tiles, Goose placement, 
class Board {
    public:
        Board(int seed = 0, bool is_seed = false);
        const std::vector<Tile *> &get_tiles() const;
        std::vector<Tile *> initialize_tiles(std::vector<Goal *> &goals, int seed = 0, bool with_seed = false);

    private:
        std::vector<Goal *> all_goals;
        std::vector<Criterion *>all_criterias;
        std::vector<Tile *> tiles;
        Tile *goose_tile;

        // Attach criterions to all tiles 
        void link_criteria();

        // attach goals to all tiles
        void link_goals();

        friend class Tile;
};

#define MAX_TILES 19

// Available ressources
enum class Ressources {
    CAFFEINE,
    LAB,
    LECTURE,
    STUDY,
    TUTORIAL,
    NETFLIX
};


// convert class name to string valued name
std::string RessourceToString(Ressources ressource);

#endif