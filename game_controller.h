#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <map>

using std::string;

#include "board.h"

struct Player;

#define NUM_PLAYERS 4
#define MIN_ROLL 2
#define MAX_ROLL 12


const string invalid_message = "Invalid command.";
const string invalid_resources = "You do not have enough resources";
const string invalid_place = "You cannot build here";
const string invalid_student = "Not a valid student";
const string has_goose = "Tile already has goose";
const string invalid_tile = "Not a valid tile";

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

        // returns the index of the player based on their color
        int color_to_name(const string &color) const;

        void print_turn() const;
        void print_status() const;

        bool game_over() const;
        void check_roll(const int roll);

        void remove_resource(const Resources name, Player &player);
        void add_resource(const Resources name, Player &player);

        void move_geese();
        void resources_7();
        void remove_random(const int resources_lost, Player &player, std::map<Resources, int> &lost);
        void steal(int location);
        void steal_output(int loser, Resources resource) const;

        void save_game(const string &filename) const;
        void output_player(std::ostream &out, const int idx) const;
        void output_board(std::ostream &out) const;

        bool is_criterion_owned(const int pos) const;
        bool is_goal_owned(const int pos) const;
        bool is_color(string &s) const;
        bool is_resource(string &s) const;

        bool tile_error(int tile);
        bool goose_error(int tile);

        int get_total_resources(const int player_idx) const;
        int get_criterion() const;

        Player *get_criterion_owner(const int pos);
        bool can_complete(const int pos) const;

        bool play();

    private:
        // helper functions for can_complete()
        bool check_complete_0(const int pos) const;
        bool check_complete_1(const int pos) const;
        bool check_complete_2(const int pos) const;
        bool check_complete_3(const int pos) const;
        bool check_complete_4(const int pos) const;
        bool check_complete_5(const int pos) const;
};

#endif