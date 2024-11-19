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
}

const std::vector<Tile *> &Board::get_tiles() const{
    return tiles;
}

void Board::link_criteria() {
    int curr = 0;

    // inialize criterias
    for (int i = 0; i < MAX_TILES; i++) {
        // conditional check for left and right criterias
        if (i == 0) {
            tiles[i]->criterias[2] = all_criterias[3];
            tiles[i]->criterias[3] = all_criterias[4];
            tiles[i]->criterias[4] = all_criterias[8];
            tiles[i]->criterias[5] = all_criterias[9];
        }
        else if (i <= 2 || i == MAX_TILES - 1) {
            tiles[i]->criterias[2] = all_criterias[curr + 5];
            tiles[i]->criterias[3] = all_criterias[curr + 6];

            // bro is special
            if (i == MAX_TILES - 1) {
                tiles[i]->criterias[4] = all_criterias[curr + 8];
                tiles[i]->criterias[5] = all_criterias[curr + 9];
            }
            else {
                // bottom two criterias
                tiles[i]->criterias[4] = all_criterias[curr + 11];
                tiles[i]->criterias[5] = all_criterias[curr + 12];
            }
        }
        else {
            // left and right criterias
            tiles[i]->criterias[2] = all_criterias[curr + 6];
            tiles[i]->criterias[3] = all_criterias[curr + 7];

            // bottom 3 tiles are special
            if (i >= 16) {
                tiles[i]->criterias[4] = all_criterias[curr + 11];
                tiles[i]->criterias[5] = all_criterias[curr + 12];
            }
            else {
                // bottom two criterias
                tiles[i]->criterias[4] = all_criterias[curr + 12];
                tiles[i]->criterias[5] = all_criterias[curr + 13];
            }
        }

        for (int j = 0; j < 6; j++) {
            if (tiles[i]->criterias[j]) {
                if ((tiles[i]->criterias[j])->get_tile() == nullptr) continue;

                tiles[i]->criterias[j]->set_tile(tiles[i]);
            }
        }

        tiles[i]->criterias[0] = all_criterias[curr];
        curr++;
        tiles[i]->criterias[1] = all_criterias[curr];
        curr++;

        // make this the algorithm form maybe
        if (i == MAX_TILES - 2) curr += 3;
        else if (i == 5 ||  i == 7 || i == 10 || i == 12 || i == 15) curr++;

    }
}

void Board::link_goals() {
    // TODO
}

// returns: vector with all tiles present in the board
std::vector<Tile *> Board::initialize_tiles(std::vector<Goal *> &goals, int seed, bool with_seed) {

    // Possible ressources for a board
    std::vector<Ressources> all_ressources = 
    {Ressources::TUTORIAL,
     Ressources::TUTORIAL,
     Ressources::TUTORIAL,
     Ressources::STUDY,
     Ressources::STUDY,
     Ressources::STUDY,
     Ressources::CAFFEINE,
     Ressources::CAFFEINE,
     Ressources::CAFFEINE,
     Ressources::CAFFEINE,
     Ressources::LAB,
     Ressources::LAB,
     Ressources::LAB,
     Ressources::LAB,
     Ressources::LECTURE,
     Ressources::LECTURE,
     Ressources::LECTURE,
     Ressources::LECTURE,
     Ressources::NETFLIX};
    
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

    std::vector<Tile *> tiles(MAX_GOAL, nullptr);

    // Initialize tiles
    for (int i = 0; i < MAX_TILES; i++) {
        Ressources ressource = all_ressources[randomized_idx[i]];
        // if the random ressource is Netflix, set the die_value to 0, indicating there is no value to get ressource
        int die_value = ressource == Ressources::NETFLIX ? 0 : die_values[randomized_idx[i]];

        Tile *curr_tile = new Tile{ressource, i, die_value, this};
        if (die_value == 0) curr_tile->has_goose = true;
        tiles[i] = curr_tile;
    }


    return tiles;
}


// General functions

// returns: string value of ressource
std::string RessourceToString(Ressources ressource) {
    switch (ressource) {
        case Ressources::CAFFEINE:
            return "CAFFEINE";
        case Ressources::LAB:
            return "LAB";
        case Ressources::LECTURE:
            return "LECTURE";
        case Ressources::STUDY:
            return "STUDY";
        case Ressources::TUTORIAL:
            return "TUTORIAL";
        case Ressources::NETFLIX:
            return "NETFLIX";
        default:
            throw std::invalid_argument("Invalid Ressources value");
    }
}