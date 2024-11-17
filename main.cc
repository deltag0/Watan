#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <exception>

#include "board.h"
#include "criterion.h"
#include "goal.h"

using std::string;
using std::cout;

int main(int argc, char *argv[]) {
    int seed;
    bool is_seed = false;
    string game;
    string loaded_board;

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

    for (auto tile: board.get_tiles()) {
        // for (int i = 0; i < 6; i++) {
            
        // }
        // cout << '\n';
        cout << tile->get_roll_val() << std::endl;
    }
}
