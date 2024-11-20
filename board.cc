#include <string>
#include <random>
#include <algorithm>
#include <iostream>

#include "stdexcept"
#include "board.h"


Board::Board(int seed, bool is_seed): all_goals(MAX_GOAL, nullptr), all_criterias(MAX_CRITERION, nullptr) {
    // Initializing every goal
    for (int i = 0; i < MAX_GOAL; i++) {
        all_goals[i] = new Goal{i};
    }
    // Initializing every criterion
    for (int i = 0; i < MAX_CRITERION; i++) {
        all_criterias[i] = new Criterion{i};
    }

    tiles = initialize_tiles(all_goals, seed, is_seed);
    link_criteria();
    link_goals();
    // for (Tile *&t : tiles) {  <-- debug_print
    //     std::cout << "Tile " << t->get_pos() << ":" << "\n";
    //     std::cout << "Criteria 0:" << t->criteria[0]->get_pos() << "\n";
    //     std::cout << "Criteria 1:" << t->criteria[1]->get_pos() << "\n";
    //     std::cout << "Criteria 2:" << t->criteria[2]->get_pos() << "\n";
    //     std::cout << "Criteria 3:" << t->criteria[3]->get_pos() << "\n";
    //     std::cout << "Criteria 4:" << t->criteria[4]->get_pos() << "\n";
    //     std::cout << "Criteria 5:" << t->criteria[5]->get_pos() << "\n";

    //     std::cout << "Goal 0:" << t->goals[0]->get_pos() << "\n";
    //     std::cout << "Goal 1:" << t->goals[1]->get_pos() << "\n";
    //     std::cout << "Goal 2:" << t->goals[2]->get_pos() << "\n";
    //     std::cout << "Goal 3:" << t->goals[3]->get_pos() << "\n";
    //     std::cout << "Goal 4:" << t->goals[4]->get_pos() << "\n";
    //     std::cout << "Goal 5:" << t->goals[5]->get_pos() << "\n" << std::endl;
    // }
}

const std::vector<Tile *> &Board::get_tiles() const{
    return tiles;
}

void Board::link_criteria() {
    int curr = 0;

    // set up criteriions
    for (int i = 0; i < MAX_TILES; i++) {
        if (i == 0) {
            tiles[i]->criteria[2] = all_criterias[3];
            tiles[i]->criteria[3] = all_criterias[4];
            tiles[i]->criteria[4] = all_criterias[8];
            tiles[i]->criteria[5] = all_criterias[9];
        }
        else if (i <= 2 || i == MAX_TILES - 1) {
            tiles[i]->criteria[2] = all_criterias[curr + 5];
            tiles[i]->criteria[3] = all_criterias[curr + 6];

            // bro is special
            if (i == MAX_TILES - 1) {
                tiles[i]->criteria[4] = all_criterias[curr + 8];
                tiles[i]->criteria[5] = all_criterias[curr + 9];
            }
            else {
                // set up bottom two criteria
                tiles[i]->criteria[4] = all_criterias[curr + 11];
                tiles[i]->criteria[5] = all_criterias[curr + 12];
            }
        }
        else {  // set up most tiles. All except 0, 1, 2, 18
            // set up left and right criteria
            tiles[i]->criteria[2] = all_criterias[curr + 6];
            tiles[i]->criteria[3] = all_criterias[curr + 7];

            // bottom 3 tiles (16, 17, 18) are special
            if (i >= 16) {
                tiles[i]->criteria[4] = all_criterias[curr + 11];
                tiles[i]->criteria[5] = all_criterias[curr + 12];
            }
            else {
                // set up bottom two criteria
                tiles[i]->criteria[4] = all_criterias[curr + 12];
                tiles[i]->criteria[5] = all_criterias[curr + 13];
            }
        }

        // set up top two criteria
        tiles[i]->criteria[0] = all_criterias[curr];
        curr++;
        tiles[i]->criteria[1] = all_criterias[curr];
        curr++;

        // put this in another function maybe?
        // For each criteria, set corresponding tile to tile at earliest position
        for (int j = 0; j < CORNERS; j++) {
            if (tiles[i]->criteria[j]->get_tile() == nullptr) {
                tiles[i]->criteria[j]->set_tile(tiles[i]);
            }
        }

        // make this the algorithm form maybe
        if (i == MAX_TILES - 2) curr += 3;
        else if (i == 5 ||  i == 7 || i == 10 || i == 12 || i == 15) curr++;

    }
}

void Board::link_goals() {
    int add_bl = -1;  // hacky variable used to calculate bottom left goal from top left goal
    int add_b = -1;  // hacky variable used to calculate bottom goal from top goal
    // initialized to avoid compiler warnings

    for (int i = 0; i < MAX_TILES; ++i) {
        switch (i) {  // special cases
            case 0:
                tiles[i]->goals[0] = all_goals[0];
                tiles[i]->goals[1] = all_goals[1];
                add_bl = 5;
                add_b = 10;
                break;
            case 1:
                tiles[i]->goals[0] = all_goals[3];
                tiles[i]->goals[1] = all_goals[5];
                add_bl = 8;
                add_b = 15;
                break;
            case 2:
                tiles[i]->goals[0] = all_goals[4];
                break;
            case 3:
                tiles[i]->goals[0] = all_goals[9];
                tiles[i]->goals[1] = all_goals[12];
                add_b = 17;
                break;
            case 5:
                tiles[i]->goals[0] = all_goals[11];
                break;
            case 6:
                add_bl = 9;
                add_b = 17;
                break;
            case 8:
                tiles[i]->goals[1] = all_goals[29];
                add_bl = 8;
                break;
            case 11:
                add_bl = 9;
                break;
            case 13:
                tiles[i]->goals[1] = all_goals[46];
                add_bl = 8;
                break;
            case 16:
                add_b = 15;
                break;
            case 18:
                add_bl = 5;
                add_b = 10;
                break;
        }

        if (tiles[i]->get_top()) {  // if tile above exists
            tiles[i]->goals[0] = all_goals[tiles[i]->get_top()->goals[5]->get_pos()];  // top goal is bottom goal of tile above
        }
        if (tiles[i]->get_top_left()) {  // if tile in top left exists
            tiles[i]->goals[1] = all_goals[tiles[i]->get_top_left()->goals[4]->get_pos()];  // top left goal is bottom right goal of top left tile
        }

        tiles[i]->goals[2] = all_goals[tiles[i]->goals[1]->get_pos() + 1];  // top right goal is top left goal + 1
        tiles[i]->goals[3] = all_goals[tiles[i]->goals[1]->get_pos() + add_bl];  // bottom left goal is top left goal + add_bl
        tiles[i]->goals[4] = all_goals[tiles[i]->goals[3]->get_pos() + 1];  // bottom right goal is bottom left goal + 1
        tiles[i]->goals[5] = all_goals[tiles[i]->goals[0]->get_pos() + add_b];  // bottom goal is top goal + add_b

        for (Goal *&g : tiles[i]->goals) {  // set tile pointer in every goal on current tile to current tile
            if (!g->get_tile()) {  // tile pointer of g is not already pointing to a tile
                g->set_tile(tiles[i]);
            }
        }
    }
}

// returns: vector with all tiles present in the board
std::vector<Tile *> Board::initialize_tiles(std::vector<Goal *> &goals, int seed, bool with_seed) {

    // Possible resources for a board
    std::vector<Resources> all_resources = 
    {Resources::TUTORIAL,
     Resources::TUTORIAL,
     Resources::TUTORIAL,
     Resources::STUDY,
     Resources::STUDY,
     Resources::STUDY,
     Resources::CAFFEINE,
     Resources::CAFFEINE,
     Resources::CAFFEINE,
     Resources::CAFFEINE,
     Resources::LAB,
     Resources::LAB,
     Resources::LAB,
     Resources::LAB,
     Resources::LECTURE,
     Resources::LECTURE,
     Resources::LECTURE,
     Resources::LECTURE,
     Resources::NETFLIX};
    
    // Possible die values for a board
    std::vector<int> die_values = 
    {2,
     12,
     3,
     3,
     4,
     4,
     5,
     5,
     6,
     6,
     8,
     8,
     9,
     9,
     10,
     10,
     11,
     11};

    std::vector<int> randomized_idx(MAX_TILES, 0);

    // initialize randomized_idx array
    for (int i = 0; i < MAX_TILES; i++) {
        randomized_idx[i] = i;
    }

    // Randomize the randomized_idx arrays by shuffling it
    // Then data from Tile i is mapped to array_with_data[randomized_idx[i]]
    std::mt19937 rng;
    if (with_seed) rng.seed(seed);
    else {
        std::random_device rd;
        rng.seed(rd());
    }

    std::shuffle(randomized_idx.begin(), randomized_idx.end(), rng);

    std::vector<Tile *> tiles(MAX_TILES, nullptr);

    // Initialize tiles
    for (int i = 0; i < MAX_TILES; i++) {
        Resources resource = all_resources[randomized_idx[i]];
        // if the random resource is Netflix, set the die_value to 0, indicating there is no value to get resource
        int die_value = resource == Resources::NETFLIX ? 0 : die_values[randomized_idx[i]];

        Tile *curr_tile = new Tile{resource, i, die_value, this};
        if (die_value == 0) curr_tile->has_goose = true;
        tiles[i] = curr_tile;
    }


    return tiles;
}

// returns true if Player player can achieve goal pos on the board
bool Board::can_achieve(int pos, Player player) const {
    int position_on_tile = 0;
    Tile *tile = all_goals[pos]->get_tile();

    for (int i = 0; i < CORNERS; i++) {
        if (tile->goals[i]->get_pos() == pos) {
            position_on_tile = i;
            break;
        }
    }

    switch (position_on_tile) {
        case 0:
            return check_goal_0(tile, player);
        case 1:
            return check_goal_1(tile, player);
        case 2:
            return check_goal_2(tile, player);
        case 3:
            return check_goal_3(tile, player);
        case 4:
            return check_goal_4(tile, player);
        case 5:
            return check_goal_5(tile, player);
        default:
            // could make this a custom error
            throw std::runtime_error("Invalid goal position.");
    }
}

bool Board::check_goal_0(Tile *tile, Player player) const {
    Tile *topright = tile->get_top_right();
    Tile *topleft = tile->get_top_left();

    if (topright && player.owns_goal(topright->goals[1]->get_pos())) {
        return true;
    }
    else if (topleft && player.owns_goal(topleft->goals[2]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[1]->get_pos()) || player.owns_goal(tile->goals[2]->get_pos())) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_1(Tile *tile, Player player) const {
    Tile *top = tile->get_top();
    Tile *botleft = tile->get_bot_left();

    if (top && player.owns_goal(top->goals[3]->get_pos())) {
        return true;
    }
    else if (botleft && player.owns_goal(botleft->goals[0]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[0]->get_pos()) || player.owns_goal(tile->goals[3]->get_pos())) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_2(Tile *tile, Player player) const {
    Tile *top = tile->get_top();
    Tile *botright = tile->get_bot_right();

    if (top && player.owns_goal(top->goals[4]->get_pos())) {
        return true;
    }
    else if (botright && player.owns_goal(botright->goals[0]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[0]->get_pos()) || player.owns_goal(tile->goals[4]->get_pos())) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_3(Tile *tile, Player player) const {
    Tile *botleft = tile->get_bot_left();
    Tile *topleft = tile->get_top_left();

    if (topleft && player.owns_goal(botleft->goals[5]->get_pos())) {
        return true;
    }
    else if (botleft && player.owns_goal(botleft->goals[4]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[1]->get_pos()) || player.owns_goal(tile->goals[5]->get_pos())) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_4(Tile *tile, Player player) const {
    Tile *topright = tile->get_top_right();
    Tile *botright = tile->get_bot_right();

    if (topright && player.owns_goal(topright->goals[5]->get_pos())) {
        return true;
    }
    else if (botright && player.owns_goal(botright->goals[3]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[5]->get_pos()) || player.owns_goal(tile->goals[2]->get_pos())) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_5(Tile *tile, Player player) const {
    Tile *botright = tile->get_bot_right();
    Tile *botleft = tile->get_bot_left();

    if (botright && player.owns_goal(botright->goals[3]->get_pos())) {
        return true;
    }
    else if (botleft && player.owns_goal(botleft->goals[4]->get_pos())) {
        return true;
    }
    else if (player.owns_goal(tile->goals[3]->get_pos()) || player.owns_goal(tile->goals[4]->get_pos())) {
        return true;
    }
    
    return false;
}

// Resource functions

// returns: string value of resource
std::string ResourceToString(Resources resource) {
    switch (resource) {
        case Resources::CAFFEINE:
            return "CAFFEINE";
        case Resources::LAB:
            return "LAB";
        case Resources::LECTURE:
            return "LECTURE";
        case Resources::STUDY:
            return "STUDY";
        case Resources::TUTORIAL:
            return "TUTORIAL";
        case Resources::NETFLIX:
            return "NETFLIX";
        default:
            throw std::invalid_argument("Invalid Resources value");
    }
}

Resources StringToResource(const std::string& resource) {
    if (resource == "CAFFEINE") {
        return Resources::CAFFEINE;
    } else if (resource == "LAB") {
        return Resources::LAB;
    } else if (resource == "LECTURE") {
        return Resources::LECTURE;
    } else if (resource == "STUDY") {
        return Resources::STUDY;
    } else if (resource == "TUTORIAL") {
        return Resources::TUTORIAL;
    } else if (resource == "NETFLIX") {
        return Resources::NETFLIX;
    } else {
        throw std::invalid_argument("Invalid resource string");
    }
}