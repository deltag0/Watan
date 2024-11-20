#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>

using std::string;

#include "board.h"
#include "player.h"

class Game_Controller {
    Board &board;
    Player p_list[NUM_PLAYERS];

    bool sot;  // True if it's the start of turn
    int turn;

    public:
        Game_Controller(Board b);

        string check_command(const string &command);
        string invalid_command() const;
        string invalid_build() const;
        string invalid_resources() const;
        int roll_dice() const;
        int color_to_name(const string &color) const;
        void print_turn() const;
        void print_status() const;
        bool game_over() const;
        void remove_resource(const Resources name, const int player);
        void add_resource(const Resources name, const int player);
        bool is_color(string &s) const;
        bool is_resource(string &s) const;
        bool play();
};

#endif