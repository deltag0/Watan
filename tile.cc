#include "tile.h"


// criteria and goals initialized with placeholder values
Tile::Tile(Resources r, int pos, int roll_value, Board *board)
: board{board}, resource{r}, pos{pos}, roll_value{roll_value}, goals(6, nullptr), criteria(6, nullptr) {}

int Tile::get_pos() const {return pos;}

int Tile::get_roll_val() const {return roll_value;}

const std::vector<Criterion *> &Tile::get_criteria() const {return criteria;}

const std::vector<Goal *> &Tile::get_goals() const {return goals;}

Tile* Tile::get_bot() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 13 || pos == 16 || pos == 18 || pos == 17 || pos == 15) return nullptr;

    if (pos == 0) return tiles[4];

    return tiles[pos + 5];
}

Tile* Tile::get_top() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 3 || pos == 1 || pos == 0 || pos == 2 || pos == 5) return nullptr;

    if (pos == 4 || pos == 18) return tiles[pos - 4];


    return tiles[pos - 5];
}

Tile* Tile::get_bot_left() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 3 || pos == 8 || pos == 13 || pos == 16 || pos == 18) return nullptr;

    if (pos == 0 || pos == 17) return tiles[pos + 1];

    return tiles[pos + 2];
}

Tile* Tile::get_top_left() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 0 || pos == 1 || pos == 3 || pos == 8 || pos == 13) return nullptr;

    if (pos == 2 || pos == 18) return tiles[pos - 2];

    return tiles[pos - 3];
}

Tile* Tile::get_top_right() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 0 || pos == 2 || pos == 5 || pos == 10 || pos == 15) return nullptr;

    if (pos == 1 || pos == 18) return tiles[pos - 1];
    
    return tiles[pos - 2];
}

Tile* Tile::get_bot_right() const {
    const std::vector<Tile *> &tiles = board->get_tiles();
    if (pos == 17 || pos == 18 || pos == 5 || pos == 10 || pos == 15) return nullptr;

    if (pos == 16 || pos == 0) return tiles[pos + 2];

    return tiles[pos + 3];
}

Resources Tile::get_resource() const{
    return resource;
}

std::string Tile::display_resource() const {
    return ResourceToString(resource) + std::string((MAX_RESOURCE_LENGTH - ResourceToString(resource).length()), ' ');
}

std::string Tile::display_roll_val() const {
    if (resource == Resources::NETFLIX) {
        return "  ";
    }
    return (roll_value < 10) ? (" " + std::to_string(roll_value)) : std::to_string(roll_value);
}

std::string Tile::display_goose() const {
    return has_goose ? "GEESE" : "     ";
}

