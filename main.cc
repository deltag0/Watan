#include <iostream>
#include <vector>
#include <string>

#include "board.h"
#include "criterion.h"
#include "goal.h"

using std::string;
using std::cout;

int main(int argc, char *argv[]) {
    string seed;
    string game;
    string loaded_board;

    for (int i = 1; i < argc; i++) {

    }

    Board board{};

    for (auto tile: board.get_tiles()) {
        for (int i = 0; i < 6; i++) {
            cout << tile->criterias[i]->display << ", ";
        }
        cout << '\n';
    }
}
