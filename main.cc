#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "board.h"
#include "criterion.h"
#include "goal.h"
#include "tiles.h"

using std::cout;

// returns: vector with all tiles present in the board
std::vector<Tile *> initialize_tiles() {

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
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(randomized_idx.begin(), randomized_idx.end(), rng);

    std::vector<Tile *> tiles(MAX_GOAL, nullptr);

    // Initialize tiles
    for (int i = 0; i < MAX_TILES; i++) {
        Ressources ressource = all_ressources[randomized_idx[i]];

        // if the random ressource is Netflix, set the die_value to 0, indicating there is no value to get ressource
        int die_value = ressource == Ressources::NETFLIX ? 0 : die_values[randomized_idx[i]];

        tiles[i] = new Tile{ressource, i, die_value};
        
    }

    return tiles;
}

int main(int argc, char *argv[]) {

    // Declaring Board assets
    std::vector<Goal *> all_goals(MAX_GOAL, nullptr);
    std::vector<Criterion *>all_criterias(MAX_CRITERION, nullptr);

    // Initializing every goal
    for (int i = 0; i < MAX_GOAL; i++) {
        all_goals[i] = new Goal{i};
    }

    // Initializing every criterion
    for (int i = 0; i < MAX_CRITERION; i++) {
        all_criterias[i] = new Criterion{i};
    }

    Board board{initialize_tiles()};

    for (auto tile: board.get_tiles()) {
        cout << tile->get_roll_val() << std::endl;
    }
}
