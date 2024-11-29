#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <map>

using std::string;

#include "board.h"
#include "view.h"
#include "subject.h"

struct Player;

#define MIN_ROLL 2
#define MAX_ROLL 12

// invalid messages
const string invalid_message = "Invalid command.";
const string invalid_resources = "You do not have enough resources";
const string invalid_place = "You cannot build here";
const string invalid_student = "Not a valid student";
const string has_goose = "Tile already has goose";
const string invalid_tile = "Not a valid tile";


// Class that manages communication between player and the game of Watan
// Updates Board and View based on input
class Game_Controller: public Subject {
    Board &board;
    View &view;

    bool sot;   // True if it's the start of turn
    int turn;  // 0 if it's Blue's turn, 1 for Red's turn, and so on

    public:
        Game_Controller(Board &b, View &v, string filename = "", bool load = false);

        // allows users to play and returns true if they play again
        bool play();

    private:
        // sets up the initial completion of criteria, function does not run if a game is loaded
        void start_game();

        // check commands for start and end of turn
        string check_command(const string &command);
        string invalid_command(const string &message);

        // rolls dice based off die player owns
        int roll_dice() const;

        // returns the index of the player based on their color
        int color_to_name(const string &color) const;

        // prints whose turn it is using turn
        void print_turn() const;

        // print status of player at index turn
        void print_status() const;

        // returns true if any player has 10vp or more
        bool game_over() const;

        // react to the roll value
        void check_roll(const int roll);

        // remove a single resource of type name from player
        void remove_resource(const Resources name, Player &player);
        // add a criterion->level + 1 resource of type name to player
        void add_resource(const Resources name, Player &player, const Criterion *criterion);

        // functions for a roll of 7
        // wrapper function that handles other functions for moving the geese
        void move_geese();
        // handles removing resources from players and outputting the results
        void resources_7();
        // handles removing resources from placing the goose tile, NOT stealing
        void remove_random(const int resources_lost, Player &player, std::map<Resources, int> &lost);
        // handles removing resources from player stealing
        void steal(int location);
        // outputs stolen resource
        void steal_output(int loser, Resources resource) const;

        // functions for saving games
        // saves game to file filename
        void save_game(const string &filename) const;
        // save player to stream provided by save_game
        void output_player(std::ostream &out, const int idx) const;
        // saves board to stream provided by save_game
        void output_board(std::ostream &out) const;

        // loads player from a saved game file
        void load_player(const string &data, int idx);

        // return true if building is owned
        bool is_criterion_owned(const int pos) const;
        bool is_goal_owned(const int pos) const;
        // returns true if s is a valid player color
        bool is_color(string &s) const;
        // returns true if s is a valid resource
        bool is_resource(string &s) const;

        // return true if tile at index tile is below or above tile boundaries
        bool tile_error(int tile);
        // returns true if tile at index tile already has goose
        bool goose_error(int tile);

        // return total number of resources of player at player_idx
        int get_total_resources(const int player_idx) const;
        // gets input from user to place a criterion, and only returns a valid criterion placement (invariance) 
        int get_criterion() const;

        Player *get_criterion_owner(const int pos);
};

#endif
