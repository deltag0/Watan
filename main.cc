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
#include "textview.h"

using std::string;
using std::cout;
using std::cin;

int main(int argc, char *argv[]) {
    int seed = 0;
    bool is_seed = false;
    string filename = "";
    bool load = false;

    // handling CLI arguments
    int i = 1;

    try {
        if (argc > 3) {
            throw std::invalid_argument("You cannot use multiple flags\n");
        }
        else if (argc == 2) {
            throw std::invalid_argument("Not enough arguments provided. Perhaps you forgot the seed/filename\n");
        }
        else if (argc == 3) {
            string command = argv[1];
            if (command != "-seed" && command != "-load" && command != "-board") {
                throw std::invalid_argument("Invalid command\n");
            }
        }

    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what();
        exit(1);
    }

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
            catch(const std::out_of_range& e)
            {
                std::cerr << "Invalid seed" << '\n';
                exit(1);
            }
            catch (const std::invalid_argument &e) {
                std::cerr << "Seed must be an integer" << '\n';
                exit(1);
            }
        }
        else if (arg == "-load") {
            i++;
            try
            {
                filename = argv[i];
                load = true;

                std::ifstream ifs{filename};

                if (!ifs) throw std::runtime_error("File does not exist");

            }
            catch(const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }
        }
        else if (arg == "-board") {
            i++;
            try
            {
                filename = argv[i];
                std::ifstream ifs{filename};

                if (!ifs) throw std::runtime_error("File does not exist");

            }
            catch(const std::runtime_error &e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }
        }

        i++;
    }

    Board board{seed, is_seed, filename, load};
    TextView view{};

    Game_Controller controller{board, view, filename, load};
    bool play_again = controller.play();
    while (play_again) {  // play until user enters "no"
        Board board{seed, false, filename, false};  // generate a new random board
        Game_Controller controller{board, view, filename, false};
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        play_again = controller.play();
    }
}
