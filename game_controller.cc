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
        else return invalid_command();

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
        cout << "Student has completed the following criteria: ";
        for (auto criteria: p_list[turn].owned_criterions) {
            cout << criteria->get_pos() << " ";
        }
    }
    else if (first == "achieve") {
        //try to achieve current goal
    }
    else if (first == "complete") {
        // try to complete the goal
    }
    else if (first == "improve") {
        // try to improve
    }
    else if (first == "trade") {
        string ans;
        string partner = "";
        string give_ressource = "";
        string desired_ressource = "";
        iss >> partner >> give_ressource >> desired_ressource;

        Resources ressource1 = StringToResource(give_ressource);
        int &ressource1_count = p_list[turn].find_ressources(ressource1);

        if (ressource1_count == 0) {
            ressource_error();
            return first;
        }

        Resources ressource2 = StringToResource(desired_ressource);

        cout << p_list[turn].name << " offers " << partner << " one " << " give_ressource "
        << " for one " << desired_ressource << ".\n" << "Does " << partner << " acceot this offer?" << '\n';\

        cin >> ans;

        if (ans == "yes") {
            int student2 = color_to_name(partner);
            int &ressource2_count = p_list[student2].find_ressources(ressource2);
            ressource1_count--;
            ressource2_count++;
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
    else return invalid_command();

    return first;
}

void Game_Controller::print_turn() const {
    cout << "Student " << p_list[turn].name << "'s " << "turn" << std::endl;
}

bool Game_Controller::game_over() const {
    return p_list[0].won() || p_list[1].won() || p_list[2].won() || p_list[3].won();
}

void Game_Controller::print_status() const {cout << p_list[turn];}

string Game_Controller::invalid_command() {
    string new_command = "";

    cout << "Invalid command." << '\n';
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

        while (roll > 12 || roll < 2) {
            cout << "Input a roll between 2 and 12: ";
            cin >> roll;

            if (roll > 12 || roll < 2) cout << "Invalid roll." << std::endl;
        }
        cin.ignore();
        return roll;
    }
}

void Game_Controller::add_ressource(const Resources name, int player) {

}

void Game_Controller::remove_ressource(const Resources name, int player) {

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

void Game_Controller::ressource_error() const {cout <<  "You do not have enough resources.\n";}