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
    int seed = 0;
    bool is_seed = false;
    string filename = "";
    bool load = false;

    // handling CLI arguments
    int i = 0;
    while (i < argc) {
        string arg = argv[i];

        if (arg == "-seed") {
            i++;
            try
            {
                string num = argv[i];
                seed = std::stoi(num);
                is_seed = true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (arg == "-load") {
            i++;
            try
            {
                filename = argv[i];
                load = true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (arg == "-board") {
            i++;
            try
            {
                filename = argv[i];
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        i++;
    }

    Board board{seed, is_seed, filename, load};


    Game_Controller controller{board, filename, load};
    bool play_again = controller.play();
    while (play_again) {  // play until user enters "no"
        play_again = controller.play();
    }
}
