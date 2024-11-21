#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>

using std::string;

#include "board.h"

struct Player;

#define NUM_PLAYERS 4
#define MIN_ROLL 2
#define MAX_ROLL 12


const string invalid_message = "Invalid command.";
const string invalid_ressources = "You do not have enough resources";
const string invalid_place = "You cannot build here";


class Game_Controller {
    Board &board;
    Player p_list[NUM_PLAYERS];

    bool sot;  // True if it's the start of turn
    int turn;

    public:
        Game_Controller(Board &b);

        string check_command(const string &command);
        string invalid_command(const string &message);
        int roll_dice() const;
        int color_to_name(const string &color) const;
        void print_turn() const;
        void print_status() const;
        bool game_over() const;
        void check_roll(const int roll);
        void remove_resource(const Resources name, Player &player);
        void add_resource(const Resources name, Player &player);

        bool is_criterion_owned(const int pos) const;
        bool is_goal_owned(const int pos) const;
        bool is_color(string &s) const;
        bool is_resource(string &s) const;

        int get_criterion() const;

        Player *get_criterion_owner(const int pos);

        bool play();
};

#endif