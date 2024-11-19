#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <exception>
#include <random>
#include <algorithm>

#include "board.h"
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
    int turn = 0;
    int players = 4;

    // our players
    Player p_list[] = {
        Player {'B'},
        Player {'R'},
        Player {'O'},
        Player {'Y'},
    };

    cout << !(p_list[0].won() || p_list[1].won() || p_list[2].won() || p_list[3].won()) << std::endl;

    // main loop
    while (!(p_list[0].won() || p_list[1].won() || p_list[2].won() || p_list[3].won())) {
        string curr = "";
        int roll = 0;

        cout << "Student " << p_list[turn].color << "'s " << "turn" << std::endl;
        cout << p_list[turn];

        // beginning of game commands
        while (curr != "roll") {
            cout << '>';
            cin >> curr;

            if (curr == "load") {
            p_list[turn].die = Dice::LOADED;
            }
            else if (curr == "fair") {
            p_list[turn].die = Dice::FAIR;
            }
            else if (curr != "roll") {
                cout << "Invalid command." << std::endl;
            }
        }

        if (p_list[turn].die == Dice::FAIR) {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> dist(2, 12);
            roll = dist(rng);

            // function for handling roll
        }
        else {
            cout << '>';

            while (roll > 12 || roll < 1) {
                cin >> roll;

                if (roll > 12 || roll < 1) cout << "Invalid command." << std::endl;
            }

        }

        turn++;
        if (turn == players) turn = 0;
    }
    

}
