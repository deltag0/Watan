#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <exception>
#include <random>
#include <algorithm>
#include <assert.h>

#include "board.h"
#include "game_controller.h"
#include "criterion.h"
#include "goal.h"
#include "player.h"

using std::string;
using std::cout;
using std::cin;

int main(int argc, char *argv[]) {
    int seed;
    bool is_seed = false;
    string game;
    string loaded_board;

    // handling CLI arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        string curr;

        std::istringstream iss{arg};
        iss >> curr;


        if (curr == "-seed") {
            try
            {
                iss >> seed;
                is_seed = true;
            }
            // figure out how to catch if input is greater than an integer
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (curr == "-load") {
            // TODO
        }
        else if (curr == "-board") {
            // TODO
        }
    }

    Board board{seed, is_seed};

    Game_Controller controller{Board{seed, is_seed}};
    bool play_again = controller.play();
    while (play_again) {  // play until user enters "no"
        play_again = controller.play();
    }
}
