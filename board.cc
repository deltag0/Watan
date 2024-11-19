#include <string>
#include <random>
#include <algorithm>
#include <iostream>

#include "stdexcept"
#include "board.h"


Board::Board(int seed, bool is_seed): all_goals(MAX_GOAL, nullptr), all_criteria(MAX_CRITERION, nullptr) {
    // Initializing every goal
    for (int i = 0; i < MAX_GOAL; i++) {
        all_goals[i] = new Goal{i};
    }
    // Initializing every criterion
    for (int i = 0; i < MAX_CRITERION; i++) {
        all_criteria[i] = new Criterion{i};
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

    // inialize criteria
    for (int i = 0; i < MAX_TILES; i++) {
        // conditional check for left and right criteria
        if (i == 0) {
            tiles[i]->criteria[2] = all_criteria[3];
            tiles[i]->criteria[3] = all_criteria[4];
            tiles[i]->criteria[4] = all_criteria[8];
            tiles[i]->criteria[5] = all_criteria[9];
        }
        else if (i <= 2 || i == MAX_TILES - 1) {
            tiles[i]->criteria[2] = all_criteria[curr + 5];
            tiles[i]->criteria[3] = all_criteria[curr + 6];

            // bro is special
            if (i == MAX_TILES - 1) {
                tiles[i]->criteria[4] = all_criteria[curr + 8];
                tiles[i]->criteria[5] = all_criteria[curr + 9];
            }
            else {
                // bottom two criteria
                tiles[i]->criteria[4] = all_criteria[curr + 11];
                tiles[i]->criteria[5] = all_criteria[curr + 12];
            }
        }
        else {
            // left and right criteria
            tiles[i]->criteria[2] = all_criteria[curr + 6];
            tiles[i]->criteria[3] = all_criteria[curr + 7];

            // bottom 3 tiles are special
            if (i >= 16) {
                tiles[i]->criteria[4] = all_criteria[curr + 11];
                tiles[i]->criteria[5] = all_criteria[curr + 12];
            }
            else {
                // bottom two criteria
                tiles[i]->criteria[4] = all_criteria[curr + 12];
                tiles[i]->criteria[5] = all_criteria[curr + 13];
            }
        }

        for (int j = 0; j < 6; j++) {
            if (tiles[i]->criteria[j]) {
                if ((tiles[i]->criteria[j])->get_tile() == nullptr) continue;

                tiles[i]->criteria[j]->set_tile(tiles[i]);
            }
        }

        tiles[i]->criteria[0] = all_criteria[curr];
        curr++;
        tiles[i]->criteria[1] = all_criteria[curr];
        curr++;

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


// General functions

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
