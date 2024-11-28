#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>

#include "stdexcept"
#include "board.h"


Board::Board(int seed, bool is_seed, std::string filename, bool load): all_goals(MAX_GOAL), all_criteria(MAX_CRITERION), tiles(MAX_TILES) {
    // Initializing every goal
    for (int i = 0; i < MAX_GOAL; i++) {
        all_goals[i] = std::make_unique<Goal>(i);
        assert(all_goals[i]);
    }
    // Initializing every criterion
    for (int i = 0; i < MAX_CRITERION; i++) {
        all_criteria[i] = std::make_unique<Criterion>(i);
        assert(all_criteria[i]);
    }

    if (filename != "") {
        // board from a saved game will AFTER the line = number of players + 1
        if (load) get_board(filename, NUM_PLAYERS + 2);
        // when only loading the board, board is on the first line
        else get_board(filename, 1);
    }
    else {
        initialize_tiles(seed, is_seed);
    }
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

const std::vector<std::unique_ptr<Tile>> &Board::get_tiles() const { return tiles; }

const std::vector<std::unique_ptr<Goal>> &Board::get_goals() const { return all_goals; }

const std::vector<std::unique_ptr<Criterion>> &Board::get_criteria() const { return all_criteria; }


void Board::link_criteria() {
    int curr = 0;

    // set up criteriions
    for (int i = 0; i < MAX_TILES; i++) {
        if (i == 0) {
            tiles[i]->criteria[2] = all_criteria[3].get();
            tiles[i]->criteria[3] = all_criteria[4].get();
            tiles[i]->criteria[4] = all_criteria[8].get();
            tiles[i]->criteria[5] = all_criteria[9].get();
        }
        else if (i <= 2 || i == MAX_TILES - 1) {
            tiles[i]->criteria[2] = all_criteria[curr + 5].get();
            tiles[i]->criteria[3] = all_criteria[curr + 6].get();

            // bro is special
            if (i == MAX_TILES - 1) {
                tiles[i]->criteria[4] = all_criteria[curr + 8].get();
                tiles[i]->criteria[5] = all_criteria[curr + 9].get();
            }
            else {
                // set up bottom two criteria
                tiles[i]->criteria[4] = all_criteria[curr + 11].get();
                tiles[i]->criteria[5] = all_criteria[curr + 12].get();
            }
        }
        else {  // set up most tiles. All except 0, 1, 2, 18
            // set up left and right criteria
            tiles[i]->criteria[2] = all_criteria[curr + 6].get();
            tiles[i]->criteria[3] = all_criteria[curr + 7].get();

            // bottom 3 tiles (16, 17, 18) are special
            if (i >= 16) {
                tiles[i]->criteria[4] = all_criteria[curr + 11].get();
                tiles[i]->criteria[5] = all_criteria[curr + 12].get();
            }
            else {
                // set up bottom two criteria
                tiles[i]->criteria[4] = all_criteria[curr + 12].get();
                tiles[i]->criteria[5] = all_criteria[curr + 13].get();
            }
        }

        // set up top two criteria
        tiles[i]->criteria[0] = all_criteria[curr].get();
        curr++;
        tiles[i]->criteria[1] = all_criteria[curr].get();
        curr++;

        // put this in another function maybe?
        // For each criteria, set corresponding tile to tile at earliest position
        for (int j = 0; j < CORNERS; j++) {
            if (tiles[i]->criteria[j]->get_tile() == nullptr) {
                tiles[i]->criteria[j]->set_tile(tiles[i].get());
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
                tiles[i]->goals[0] = all_goals[0].get();
                tiles[i]->goals[1] = all_goals[1].get();
                add_bl = 5;
                add_b = 10;
                break;
            case 1:
                tiles[i]->goals[0] = all_goals[3].get();
                tiles[i]->goals[1] = all_goals[5].get();
                add_bl = 8;
                add_b = 15;
                break;
            case 2:
                tiles[i]->goals[0] = all_goals[4].get();
                break;
            case 3:
                tiles[i]->goals[0] = all_goals[9].get();
                tiles[i]->goals[1] = all_goals[12].get();
                add_b = 17;
                break;
            case 5:
                tiles[i]->goals[0] = all_goals[11].get();
                break;
            case 6:
                add_bl = 9;
                add_b = 17;
                break;
            case 8:
                tiles[i]->goals[1] = all_goals[29].get();
                add_bl = 8;
                break;
            case 11:
                add_bl = 9;
                break;
            case 13:
                tiles[i]->goals[1] = all_goals[46].get();
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
            tiles[i]->goals[0] = all_goals[tiles[i]->get_top()->goals[5]->get_pos()].get();  // top goal is bottom goal of tile above
        }
        if (tiles[i]->get_top_left()) {  // if tile in top left exists
            tiles[i]->goals[1] = all_goals[tiles[i]->get_top_left()->goals[4]->get_pos()].get();  // top left goal is bottom right goal of top left tile
        }

        tiles[i]->goals[2] = all_goals[tiles[i]->goals[1]->get_pos() + 1].get();  // top right goal is top left goal + 1
        tiles[i]->goals[3] = all_goals[tiles[i]->goals[1]->get_pos() + add_bl].get();  // bottom left goal is top left goal + add_bl
        tiles[i]->goals[4] = all_goals[tiles[i]->goals[3]->get_pos() + 1].get();  // bottom right goal is bottom left goal + 1
        tiles[i]->goals[5] = all_goals[tiles[i]->goals[0]->get_pos() + add_b].get();  // bottom goal is top goal + add_b

        for (Goal *&g : tiles[i]->goals) {  // set tile pointer in every goal on current tile to current tile
            if (!g->get_tile()) {  // tile pointer of g is not already pointing to a tile
                g->set_tile(tiles[i].get());
            }
        }
    }
}

// returns: vector with all tiles present in the board
void Board::initialize_tiles(int seed, bool with_seed) {

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

    // vectors that will contain random indexes
    std::vector<int> randomized_resource_idx(MAX_TILES, 0);
    std::vector<int> randomized_die_idx(MAX_TILES - 1, 0);

    // initialize randomized_idx arrays
    for (int i = 0; i < MAX_TILES; i++) {
        randomized_resource_idx[i] = i;
        if (i != MAX_TILES - 1) randomized_die_idx[i] = i;
    }

    // Randomize the randomized_idx arrays by shuffling it
    // Then data from Tile i is mapped to array_with_data[randomized_idx[i]]
    std::mt19937 rng;
    if (with_seed) rng.seed(seed);
    else {
        std::random_device rd;
        rng.seed(rd());
    }

    // make indexes of vectors map to random corresponding index
    std::shuffle(randomized_resource_idx.begin(), randomized_resource_idx.end(), rng);
    std::shuffle(randomized_die_idx.begin(), randomized_die_idx.end(), rng);

    // index for resources
    int i = 0;
    // index for dice
    int j = 0;

    // Initialize tiles
    while (i < MAX_TILES) {
        Resources resource = all_resources[randomized_resource_idx[i]];

        // if the random resource is Netflix, set the die_value to 0, indicating there is no value to get resource
        int die_value = resource == Resources::NETFLIX ? 7 : die_values[randomized_die_idx[j]];

        std::unique_ptr<Tile> curr_tile{new Tile{resource, i, die_value, this}};
        if (die_value == 7) {
            goose_tile = curr_tile.get();
            curr_tile->has_goose = true;
            j--;
        }
        tiles[i] = std::move(curr_tile); // make sure this works

        i++;
        j++;
    }
}

// need to add line parameter to know which line the board info is at
void Board::get_board(const std::string &filename, int line_num) {
    std::ifstream ifs{filename};
    std::string line = "";

    for (int i = 0; i < line_num; i++) {
        std::getline(ifs, line);
    }

    std::istringstream iss{line};

    for (int i = 0; i < MAX_TILES; i++) {
        int resource_num = 0;
        int roll_val = 0;
        iss >> resource_num >> roll_val;

        std::unique_ptr<Tile> curr_tile{new Tile{NumToResource(resource_num), i, roll_val, this}};
        tiles[i] = std::move(curr_tile); // make sure this works with owneership
    }
    std::getline(ifs, line);
    std::istringstream iss2{line};
    int goose = 0;
    iss2 >> goose;

    goose_tile = tiles[goose].get();
    goose_tile->has_goose = true;
}

// returns true if Player player can connect the goal (but doesn't verify resources)
bool Board::can_achieve(int pos, Player player) const {
    if (all_goals[pos]->get_player() != nullptr) {
        return false;
    }

    int position_on_tile = 0;
    Tile *tile = all_goals[pos]->get_tile();

    for (int i = 0; i < CORNERS; i++) {
        if (tile->goals[i]->get_pos() == pos) {
            position_on_tile = i;
            break;
        }
    }


    assert(position_on_tile >= 0 && position_on_tile < 6);


    if ((position_on_tile == 5 && (player.owns_criterion(tile->get_criteria()[4]->get_pos()) || player.owns_criterion(tile->get_criteria()[5]->get_pos()))) ||
    (position_on_tile == 0 && (player.owns_criterion(tile->get_criteria()[0]->get_pos()) || player.owns_criterion(tile->get_criteria()[1]->get_pos()))) ||
    ((position_on_tile != 0 && position_on_tile != 5) &&
    (player.owns_criterion(tile->get_criteria()[position_on_tile - 1]->get_pos()) || player.owns_criterion(tile->get_criteria()[position_on_tile + 1]->get_pos()))))
    {
        return true;
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

    bool in_the_way_right = tile->get_criteria()[1]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[0]->in_the_way(&player);

    if (!in_the_way_right && topright && player.owns_goal(topright->goals[1]->get_pos())) {
        return true;
    }
    else if (!in_the_way_left && topleft && player.owns_goal(topleft->goals[2]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_left && player.owns_goal(tile->goals[1]->get_pos())) 
            || (!in_the_way_right && player.owns_goal(tile->goals[2]->get_pos()))) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_1(Tile *tile, Player player) const {
    Tile *top = tile->get_top();
    Tile *botleft = tile->get_bot_left();

    bool in_the_way_right = tile->get_criteria()[0]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[2]->in_the_way(&player);

    if (!in_the_way_right && top && player.owns_goal(top->goals[3]->get_pos())) {
        return true;
    }
    else if (!in_the_way_left && botleft && player.owns_goal(botleft->goals[0]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_right && player.owns_goal(tile->goals[0]->get_pos())) 
        || (!in_the_way_left && player.owns_goal(tile->goals[3]->get_pos()))) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_2(Tile *tile, Player player) const {
    Tile *top = tile->get_top();
    Tile *botright = tile->get_bot_right();

    bool in_the_way_right = tile->get_criteria()[3]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[1]->in_the_way(&player);

    if (!in_the_way_left && top && player.owns_goal(top->goals[4]->get_pos())) {
        return true;
    }
    else if (!in_the_way_right && botright && player.owns_goal(botright->goals[0]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_left && player.owns_goal(tile->goals[0]->get_pos())) 
            || (!in_the_way_right && player.owns_goal(tile->goals[4]->get_pos()))) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_3(Tile *tile, Player player) const {
    Tile *botleft = tile->get_bot_left();
    Tile *topleft = tile->get_top_left();

    bool in_the_way_right = tile->get_criteria()[4]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[2]->in_the_way(&player);

    if (!in_the_way_left && topleft && player.owns_goal(topleft->goals[5]->get_pos())) {
        return true;
    }
    else if (!in_the_way_right && botleft && player.owns_goal(botleft->goals[4]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_left && player.owns_goal(tile->goals[1]->get_pos())) 
            || (!in_the_way_right && player.owns_goal(tile->goals[5]->get_pos()))) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_4(Tile *tile, Player player) const {
    Tile *topright = tile->get_top_right();
    Tile *botright = tile->get_bot_right();

    bool in_the_way_right = tile->get_criteria()[3]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[5]->in_the_way(&player);

    if (!in_the_way_right && topright && player.owns_goal(topright->goals[5]->get_pos())) {
        return true;
    }
    else if (!in_the_way_left && botright && player.owns_goal(botright->goals[3]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_left && player.owns_goal(tile->goals[5]->get_pos())) 
            || (!in_the_way_right && player.owns_goal(tile->goals[2]->get_pos()))) {
        return true;
    }
    
    return false;
}

bool Board::check_goal_5(Tile *tile, Player player) const {
    Tile *botright = tile->get_bot_right();
    Tile *botleft = tile->get_bot_left();

    bool in_the_way_right = tile->get_criteria()[5]->in_the_way(&player);
    bool in_the_way_left = tile->get_criteria()[4]->in_the_way(&player);

    if (!in_the_way_right && botright && player.owns_goal(botright->goals[3]->get_pos())) {
        return true;
    }
    else if (!in_the_way_left && botleft && player.owns_goal(botleft->goals[4]->get_pos())) {
        return true;
    }
    else if ((!in_the_way_left && player.owns_goal(tile->goals[3]->get_pos())) 
            || (!in_the_way_right && player.owns_goal(tile->goals[4]->get_pos()))) {
        return true;
    }
    
    return false;
}

const Tile *Board::get_goose() const {return goose_tile;}

void Board::set_goose(Tile *tile) {
    assert(goose_tile);
    goose_tile->has_goose = false;
    goose_tile = tile;
    tile->has_goose = true;
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

int ResourceToNum(Resources resource) {
    switch (resource) {
        case Resources::CAFFEINE:
            return 0;
        case Resources::LAB:
            return 1;
        case Resources::LECTURE:
            return 2;
        case Resources::STUDY:
            return 3;
        case Resources::TUTORIAL:
            return 4;
        case Resources::NETFLIX:
            return 5;
        default:
            throw std::invalid_argument("Invalid Resources value");
    }
}

Resources NumToResource(int num) {
    switch (num) {
        case 0:
            return Resources::CAFFEINE;
        case 1:
            return Resources::LAB;
        case 2:
            return Resources::LECTURE;
        case 3:
            return Resources::STUDY;
        case 4:
            return Resources::TUTORIAL;
        case 5:
            return Resources::NETFLIX;
        default:
            throw std::invalid_argument("Invalid number for Resources");
    }
}
