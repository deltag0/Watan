#include <iostream>
#include <sstream>
#include <stdexcept>
#include <random>
#include <algorithm>

#include "game_controller.h"

using std::cout;
using std::cin;
using std::string;

Game_Controller::Game_Controller(Board b): board{b}, 
p_list{Player {'B', "Blue"},
        Player {'R', "Red"},
        Player {'O', "Orange"},
        Player {'Y', "Yellow"},}, sot{true}, turn{0} {}

bool Game_Controller::play() {

    for (int i = 0; i < NUM_PLAYERS; i++) {
        int pos = 0;
        cout << "Student " << p_list[i].name << ", where do you want to complete an Assignment?\n";

        pos = get_criterion();

        while (is_criterion_owned(pos)) {
            cout << invalid_place << '\n';
            pos = get_criterion();
        }

        p_list[i].owned_criterions.insert(pos);
    }
    for (int i = NUM_PLAYERS - 1; i >= 0; i--) {
        int pos = 0;
        cout << "Student " << p_list[i].name << ", where do you want to complete an Assignment?\n";

        pos = get_criterion();

        while (is_criterion_owned(pos)) {
            cout << invalid_place << '\n';
            pos = get_criterion();
        }
        
        p_list[i].owned_criterions.insert(pos);
    }

    // main loop
    while (!game_over()) {
        string curr = "";
        int roll;

        print_turn();
        print_status();
        cin.ignore();
        // beginning of game commands
        while (curr != "roll") {
            cout << '>';
            std::getline(cin, curr);

            curr = check_command(curr);
        }

        roll = roll_dice();

        while (curr != "next") {
            cout << '>';
            std::getline(cin, curr);

            curr = check_command(curr);
        }
    }
    
    // end of game
    string ans;
    cout << "Would you like to play again?" << std::endl;
    while (cin >> ans) {
        if (ans == "yes") {
            return true;
        }
        else if (ans == "no") {
            return false;
        }
        else {
            cout << "Invalid command." << std::endl;
        }
    }
}

string Game_Controller::check_command(const string &command) {
    string first;
    std::istringstream iss{command};

    iss >> first;

    if (sot) {
        if (first == "load") {
            p_list[turn].die = Dice::LOADED;
        }
        else if (first == "fair") {
        p_list[turn].die = Dice::FAIR;
        }
        else if (first == "roll") {
            sot = false;
        }
        else return invalid_command(invalid_message);

        return first;
    }
    
    if (first == "board") {
        // print board;
    }
    else if (first == "status") {
        int save_turn = turn;
        turn = 0;
        for (int i = 0; i < NUM_PLAYERS; i++) {
            print_status();
            turn++;
        }
        turn = save_turn;
    }
    else if (first == "criteria") {
        cout << "Student has completed the following criteria:";
        for (auto criteria: p_list[turn].owned_criterions) {
            cout << " " << criteria;
        }
        cout << std::endl;
    }
    else if (first == "achieve") {
        int pos;
        
        if (!(cin >> pos)) {
            return invalid_command(invalid_message);
        }
        
        bool can_achieve = board.can_achieve(pos, p_list[turn]);

        if (!can_achieve) {
            return invalid_command(invalid_place);
        }

        if (p_list[turn].study_count == 0 || p_list[turn].tutorial_count == 0) {
            return invalid_command(invalid_ressources);
        }

        p_list[turn].study_count--;
        p_list[turn].tutorial_count--;
        
        p_list[turn].owned_goal.insert(pos);
    }
    else if (first == "complete") {
        
    }
    else if (first == "improve") {
        // try to improve criteria at criteria #
    }
    else if (first == "trade") {
        string ans;
        string partner;
        string give_resource;
        string take_resource;
        if (!(iss >> partner >> give_resource >> take_resource) 
        || !is_color(partner) 
        || partner == p_list[turn].name
        || !is_resource(give_resource) 
        || !is_resource(take_resource)) {
            return invalid_command(invalid_message);
        }
        
        Resources resource1 = StringToResource(give_resource);
        int &resource1_count = p_list[turn].find_resources(resource1);

        if (resource1_count == 0) {
            return invalid_command(invalid_ressources);
        }

        Resources resource2 = StringToResource(take_resource);

        cout << p_list[turn].name << " offers " << partner << " one " << " give_resource "
        << " for one " << take_resource << ".\n" << "Does " << partner << " accept this offer?" << '\n';\

        cin >> ans;

        if (ans == "yes") {
            int student2 = color_to_name(partner);
            int &resource2_count = p_list[student2].find_resources(resource2);
            resource1_count--;
            resource2_count++;
        }
    }
    else if (first == "next") {
        sot = true;
        turn++;
        if (turn == NUM_PLAYERS) turn = 0;
    }
    else if (first == "save") {
        // save the game
    }
    else if (first == "help") {
        cout << "Valid commands:\n"
        << " board\n"
        << " status\n"
        << " criteria\n"
        << " achieve <goal>\n"
        << " complete <criterion>\n"
        << " improve <criterion>\n"
        << " trade <colour> <give> <take>\n"
        << " next\n"
        << " save <file>\n"
        << " help" << std::endl;
    }
    else return invalid_command(invalid_message);

    return first;
}

void Game_Controller::print_turn() const {
    cout << "Student " << p_list[turn].name << "'s " << "turn." << std::endl;
}

bool Game_Controller::game_over() const {
    return p_list[0].won() || p_list[1].won() || p_list[2].won() || p_list[3].won();
}

void Game_Controller::print_status() const {cout << p_list[turn];}

string Game_Controller::invalid_command(const string &message) {
    string new_command = "";

    cout << message << '\n';
    cout << '>';

    std::getline(cin, new_command);

    return check_command(new_command);
}

int Game_Controller::roll_dice() const {
    if (p_list[turn].die == Dice::FAIR) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(2, 12);
        return dist(rng);
    }
    else {
        int roll = 0;

        while (roll > MAX_ROLL || roll < MIN_ROLL) {  // while invalid roll
            cout << "Input a roll between 2 and 12: ";
            cin >> roll;

            if (roll > MAX_ROLL || roll < MIN_ROLL) cout << "Invalid roll." << std::endl;
        }
        cin.ignore();
        return roll;
    }
}

int Game_Controller::get_criterion() const {
    int pos = 0;

    cout << '>';
    if (!(cin >> pos) || pos < 0 || pos > MAX_CRITERION - 1) {
        cout << "You cannot build here.\n";
        return get_criterion();
    }

    return pos;
}

bool Game_Controller::is_criterion_owned(const int pos) const {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (p_list[i].owns_criterion(pos)) {
            return true;
        }
    }
    return false;
}

bool Game_Controller::is_goal_owned(const int pos) const {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (p_list[i].owns_goal(pos)) {
            return true;
        }
    }
    return false;
}

void Game_Controller::add_resource(const Resources name, int player) {

}

void Game_Controller::remove_resource(const Resources name, int player) {

}

int Game_Controller::color_to_name(const string &color) const {
    if (color == "Blue") {
        return 0;
    } else if (color == "Red") {
        return 1;
    } else if (color == "Orange") {
        return 2;
    } else if (color == "Yellow") {
        return 3;
    } else {
        throw std::invalid_argument("Invalid color: " + color);
    }
}

bool Game_Controller::is_color(string &s) const {
    return s == "Blue" || s == "Red" || s == "Orange" || s == "Yellow";
}

bool Game_Controller::is_resource(string &s) const {
    return s == "CAFFEINE" || s == "LAB" || s == "LECTURE" || s == "STUDY" || s == "TUTORIAL";
}
