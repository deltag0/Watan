#include "game_controller.h"

#include <assert.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "player.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

Game_Controller::Game_Controller(Board &b, View &v, string filename, bool load): board{b}, view{v},sot{true}, turn{0} 
        {
            // initialize all players needed
            attach(std::unique_ptr<Player>{new Player{'B', "Blue", 0}});
            attach(std::unique_ptr<Player>{new Player{'R', "Red", 1}});
            attach(std::unique_ptr<Player>{new Player{'O', "Orange", 2}});
            attach(std::unique_ptr<Player>{new Player{'Y', "Yellow", 3}});

            // if we load game, then players must be initialized
            if (load) {
                std::ifstream ifs{filename};
                string line = "";

                ifs >> turn;
                // extra line we need to get rid of
                std::getline(ifs, line);

                for (int i = 0; i < num_observers; i++) {
                    std::getline(ifs, line);
                    load_player(line, i);
                }
                sot = false;
            }
        }

bool Game_Controller::play() {
    if (sot) { // if a game is loaded, this is ommitted
        start_game();
    }

    // main loop
    while (!game_over()) {
        string curr = "";

        // could put this in a function to make it cleaner (might not be worth)
        if (sot) {
            int roll = 0;

            // output game info
            print_turn();
            print_status();

            // beginning of game commands
            while (curr != "roll") {
                cout << '>';
                std::getline(cin, curr);
                if (cin.eof()) {
                    save_game("backup.sv");
                    exit(0);
                }

                curr = check_command(curr);
            }

            roll = roll_dice();

            check_roll(roll);
        }

        while (curr != "next") {
            cout << '>';
            std::getline(cin, curr);
            if (cin.eof()) {
                save_game("backup.sv");
                exit(0);
            }

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
            cout << invalid_command(invalid_message);
        }
    }
    if (cin.eof()) {
        save_game("backup.sv");
        exit(0);
    }
}

void Game_Controller::start_game() {
    // loop through all observers and set up initial 2 criteria
    for (int i = 0; i < num_observers; i++) {
        int pos = 0;
        cout << "Student " << p_list[i]->name << ", where do you want to complete an Assignment?\n";

        pos = get_criterion();

        while (!board.can_complete(pos, sot, *p_list[turn])) {
            cout << invalid_place << '\n';
            pos = get_criterion();
        }

        board.get_criteria()[pos]->set_player(p_list[i].get());
        string s = string{p_list[i]->color} + "A";
        board.get_criteria()[pos]->set_display(s);
        p_list[i]->owned_criterions.insert(pos);
        ++(p_list[i]->points);
    }

    for (int i = num_observers - 1; i >= 0; i--) {
        int pos = 0;
        cout << "Student " << p_list[i]->name << ", where do you want to complete an Assignment?\n";

        pos = get_criterion();

        while (!board.can_complete(pos, sot, *p_list[turn])) {
            cout << invalid_place << '\n';
            pos = get_criterion();
        }

        board.get_criteria()[pos]->set_player(p_list[i].get());
        string s = string{p_list[i]->color} + "A";
        board.get_criteria()[pos]->set_display(s);
        p_list[i]->owned_criterions.insert(pos);
        ++(p_list[i]->points);
    }
}

string Game_Controller::check_command(const string &command) {
    string first;
    std::istringstream iss{command};

    iss >> first;

    // possible commands for the start of turn and early return
    if (sot) {
        if (first == "load") {
            p_list[turn]->die = Dice::LOADED;
        } else if (first == "fair") {
            p_list[turn]->die = Dice::FAIR;
        } else if (first == "roll") {
            sot = false;
        } else
            return invalid_command(invalid_message);

        return first;
    }

    // Big if checker for the current command
    // if multiple commands are included on a single line, the program only accepts it if the
    // FIRST word is a valid command and throws out everything else
    if (first == "board") {
        view.display(board);
    } else if (first == "status") {
        notifyObservers();
    } else if (first == "criteria") {
        cout << "Student has completed the following criteria:";
        for (auto criteria : p_list[turn]->owned_criterions) {
            cout << " " << criteria;
        }
        cout << std::endl;
    } else if (first == "achieve") {
        int pos;

        if (!(iss >> pos)) {
            iss.clear();
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return invalid_command(invalid_message);
        }

        if (pos < 0 || pos >= MAX_GOAL) return invalid_command(invalid_place);

        bool can_achieve = board.can_achieve(pos, *p_list[turn]);

        if (!can_achieve) {
            return invalid_command(invalid_place);
        }

        if (p_list[turn]->study_count == 0 || p_list[turn]->tutorial_count == 0) {
            return invalid_command(invalid_resources);
        }

        p_list[turn]->study_count--;
        p_list[turn]->tutorial_count--;

        p_list[turn]->owned_goal.insert(pos);
        board.get_goals()[pos]->set_player(p_list[turn].get());
        string s = string{p_list[turn]->color} + "A";
        board.get_goals()[pos]->set_display(s);
    } else if (first == "complete") {
        int pos;
        if (!(iss >> pos)) {
            return invalid_command(invalid_message);
        }

        if (pos < 0 || pos >= MAX_CRITERION || !board.can_complete(pos, sot, *p_list[turn])) return invalid_command(invalid_place);

        if (p_list[turn]->caffeine_count < 1 || p_list[turn]->lab_count < 1 || p_list[turn]->lecture_count < 1 || p_list[turn]->tutorial_count < 1) return invalid_command(invalid_resources);

        --p_list[turn]->caffeine_count;
        --p_list[turn]->lab_count;
        --p_list[turn]->lecture_count;
        --p_list[turn]->tutorial_count;

        p_list[turn]->owned_criterions.insert(pos);
        board.get_criteria()[pos]->set_player(p_list[turn].get());
        string s = string{p_list[turn]->color} + "A";
        board.get_criteria()[pos]->set_display(s);
        ++p_list[turn]->points;
        if (p_list[turn]->points == 10) return "next";  // ends the game 
    } else if (first == "improve") {
        int pos;
        if (!(iss >> pos)) {
            return invalid_command(invalid_message);
        }

        if (pos < 0 || pos >= MAX_CRITERION || !p_list[turn]->owns_criterion(pos) || board.get_criteria()[pos]->get_level() > 1) {
            return invalid_command(invalid_place);
        }

        string s = board.get_criteria()[pos]->get_display();

        switch (board.get_criteria()[pos]->get_level()) {
            case 0:
                if (p_list[turn]->lecture_count < 2 || p_list[turn]->study_count < 3) return invalid_command(invalid_resources);

                p_list[turn]->lecture_count -= 2;
                p_list[turn]->study_count -= 3;
                s = string{p_list[turn]->color} + "M";
                break;
            case 1:
                if (p_list[turn]->caffeine_count < 3 || p_list[turn]->lab_count < 2 || p_list[turn]->lecture_count < 2 || p_list[turn]->tutorial_count < 1 || p_list[turn]->study_count < 2) return invalid_command(invalid_resources);

                p_list[turn]->caffeine_count -= 3;
                p_list[turn]->lab_count -= 2;
                p_list[turn]->lecture_count -= 2;
                --p_list[turn]->tutorial_count;
                p_list[turn]->study_count -= 2;
                s = string{p_list[turn]->color} + "E";
                break;
        }
        board.get_criteria()[pos]->increase_level();
        board.get_criteria()[pos]->set_display(s);
        ++p_list[turn]->points;
        if (p_list[turn]->points == 10) return "next";  // ends the game 
    } else if (first == "trade") {
        string ans = "";
        string partner = "";
        string give_resource = "";
        string take_resource = "";
        if (!(iss >> partner >> give_resource >> take_resource) || !is_color(partner) || partner == p_list[turn]->name || !is_resource(give_resource) || !is_resource(take_resource)) {
            return invalid_command(invalid_message);
        }

        Resources resource1 = StringToResource(give_resource);
        int &p1_give_resource = p_list[turn]->find_resources(resource1);

        if (p1_give_resource == 0) {
            return invalid_command(invalid_resources);
        }

        Resources resource2 = StringToResource(take_resource);

        cout << p_list[turn]->name << " offers " << partner << " one " << give_resource
             << " for one " << take_resource << ".\n"
             << "Does " << partner << " accept this offer?" << '\n';

        cout << '>';
        std::getline(cin, ans);
        if (cin.eof()) {
            save_game("backup.sv");
            exit(0);
        }

        while (ans != "yes" && ans != "no") {
            cout << invalid_message << '\n';
            cout << '>';
            std::getline(cin, ans);
            if (cin.eof()) {
                save_game("backup.sv");
                exit(0);
            }
        }

        if (ans == "yes") { // add resources to players
            int &p1_gain_resource = p_list[turn]->find_resources(resource2);
            int student2 = color_to_name(partner);
            int &p2_give_resource = p_list[student2]->find_resources(resource2);
            int &p2_gain_resource = p_list[student2]->find_resources(resource1);

            p1_gain_resource++;
            p1_give_resource--;
            p2_gain_resource++;
            p2_give_resource--;
        }
    } else if (first == "next") { // player ended turn
        sot = true;
        turn++;
        if (turn == num_observers) turn = 0;
    } else if (first == "save") {
        string filename = "";
        if (!(iss >> filename)) return invalid_command(invalid_message);

        save_game(filename);
    } else if (first == "help") {
        cout << "Valid commands:\n"
             << "board\n"
             << "status\n"
             << "criteria\n"
             << "achieve <goal>\n"
             << "complete <criterion>\n"
             << "improve <criterion>\n"
             << "trade <player> <give> <take>\n"
             << "next\n"
             << "save <filename>\n"
             << "help\n";
    } else {
        return invalid_command(invalid_message);
    }

    return first;
}


void Game_Controller::print_turn() const {
    cout << "Student " << p_list[turn]->name << "'s " << "turn." << std::endl;
}

bool Game_Controller::game_over() const {
    for (int i = 0; i < num_observers; i++) {
        if (p_list[0]->won()) return true;
    }

    return false;
}

void Game_Controller::check_roll(const int roll) {
    std::map<Resources, vector<int>> resources_gained;
    bool gained = false;

    // initialize a map for easy access of gained resources
    for (Resources resource : {Resources::CAFFEINE, Resources::LAB, Resources::LECTURE,
                               Resources::STUDY, Resources::TUTORIAL}) {
        for (int i = 0; i < num_observers; i++) {
            resources_gained[resource].push_back(0);
        }
    }

    if (roll == 7) {
        move_geese();
        return;
    }

    // check tiles with corresponding roll
    for (auto &tile : board.get_tiles()) {
        assert(tile);
        if (tile->get_roll_val() == roll) {
            vector<Criterion *> criterias = tile->get_criteria();

            for (auto criteria : criterias) {
                assert(criteria);
                Player *owner = get_criterion_owner(criteria->get_pos());

                if (owner) {
                    gained = true;
                    add_resource(tile->get_resource(), *owner, criteria);
                    resources_gained[tile->get_resource()][owner->idx] += criteria->get_level() + 1;
                }
            }
        }
    }

    for (int i = 0; i < num_observers; i++) {
        string output = "";
        for (Resources resource : {Resources::CAFFEINE, Resources::LAB, Resources::LECTURE,
                                   Resources::STUDY, Resources::TUTORIAL}) {
            int gained = resources_gained[resource][i];

            if (gained > 0) {
                output += std::to_string(gained) + " " + ResourceToString(resource) + '\n';
            }
        }
        if (output != "") {
            cout << "Student " << p_list[i]->name << " gained:\n";
            cout << output;
        }
    }

    if (!gained) {
        cout << "No students gained resources.\n";
    }
}

void Game_Controller::print_status() const { cout << *p_list[turn]; }

string Game_Controller::invalid_command(const string &message) {
    string new_command = "";

    cout << message << '\n';
    cout << '>';

    std::getline(cin, new_command);
    if (cin.eof()) {
        save_game("backup.sv");
        exit(0);
    }

    // recursively call check_command until valid input is received
    return check_command(new_command);
}

int Game_Controller::roll_dice() const {
    // randomly roll
    if (p_list[turn]->die == Dice::FAIR) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(2, 12);
        return dist(rng);
    } else { // get input
        int roll = 0;

        string line = "";

        cout << "Input a roll between 2 and 12: ";

        std::getline(cin, line);

        std::istringstream iss{line};

        while (!(iss >> roll) || roll > MAX_ROLL || roll < MIN_ROLL) {  // while invalid roll
            if (cin.eof()) {
                save_game("backup.sv");
                exit(0);
            }
            cout << "Invalid roll.\n";
            cout << "Input a roll between 2 and 12: ";

            iss.clear();
            std::getline(cin, line);
            iss.str(line);
        }

        return roll;
    }
}

int Game_Controller::get_criterion() const {
    string line = "";
    int pos = 0;


    cout << '>';
    std::getline(cin, line);
    std::istringstream iss{line};

    if (!(iss >> pos) || pos < 0 || pos >= MAX_CRITERION) {
        if (cin.eof()) {
            save_game("backup.sv");
            exit(0);
        }
        if (iss) cout << invalid_place << '\n';
        else cout << invalid_message << '\n';
        return get_criterion();
    }

    return pos;
}

bool Game_Controller::is_criterion_owned(const int pos) const {
    for (int i = 0; i < num_observers; i++) {
        if (p_list[i]->owns_criterion(pos)) {
            return true;
        }
    }
    return false;
}

Player *Game_Controller::get_criterion_owner(const int pos) {
    for (int i = 0; i < num_observers; i++) {
        if (p_list[i]->owns_criterion(pos)) {
            return (p_list[i].get());
        }
    }
    return nullptr;
}

bool Game_Controller::is_goal_owned(const int pos) const {
    for (int i = 0; i < num_observers; i++) {
        if (p_list[i]->owns_goal(pos)) {
            return true;
        }
    }
    return false;
}


void Game_Controller::add_resource(const Resources name, Player &player, const Criterion *criterion) {
    switch (name) {
        case Resources::CAFFEINE:
            player.caffeine_count += criterion->get_level() + 1;
            break;
        case Resources::LAB:
            player.lab_count += criterion->get_level() + 1;
            break;
        case Resources::LECTURE:
            player.lecture_count += criterion->get_level() + 1;
            break;
        case Resources::STUDY:
            player.study_count += criterion->get_level() + 1;
            break;
        case Resources::TUTORIAL:
            player.tutorial_count += criterion->get_level() + 1;
            break;
        default:
            break;
    }
}


void Game_Controller::remove_resource(const Resources name, Player &player) {
    switch (name) {
        case Resources::CAFFEINE:
            player.caffeine_count--;
            break;
        case Resources::LAB:
            player.lab_count--;
            break;
        case Resources::LECTURE:
            player.lecture_count--;
            break;
        case Resources::STUDY:
            player.study_count--;
            break;
        case Resources::TUTORIAL:
            player.tutorial_count--;
            break;
        default:
            throw std::invalid_argument("Did not provide a valid resource to remove");
            break;
    }
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

void Game_Controller::move_geese() {
    resources_7();

    cout << "Choose where to place the GEESE.\n";
    int location = 0;
    string line = "";
    cout << '>';

    std::getline(cin, line);

    std::istringstream iss{line};

    while (!(iss >> location) || tile_error(location) || goose_error(location)) {
        if (cin.eof()) {
            save_game("backup.sv");
            exit(0);
        }
        // if input went through, then specify error message
        if (iss) {
            if (tile_error(location))
                cout << invalid_place << '\n';
            else
                cout << has_goose << '\n';
        }
        else cout << invalid_message << '\n';

        cout << '>';
        iss.clear();
        std::getline(cin, line);
        iss.str(line);
    }

    board.set_goose(board.get_tiles()[location].get());
    steal(location);
}

void Game_Controller::resources_7() {
    for (int i = 0; i < num_observers; i++) {
        int total_resources = get_total_resources(i);
        std::map<Resources, int> resources_lost;

        // condition to remove resources from all players
        if (total_resources >= 10) {
            remove_random(total_resources / 2, *p_list[i], resources_lost);

            cout << "Student " << p_list[i]->name << " loses " << total_resources / 2 << " resources to the geese. They lose:\n";

            for (auto const &[resource, count] : resources_lost) {
                if (count != 0) {
                    std::cout << count << " " << ResourceToString(resource) << '\n';
                }
            }
        }
    }
}

bool Game_Controller::tile_error(int tile) { return tile < 0 || tile >= MAX_TILES; }

bool Game_Controller::goose_error(int tile) { return board.get_tiles()[tile]->has_goose; }

void Game_Controller::remove_random(const int resources_lost, Player &player, std::map<Resources, int> &lost) {
    int i = 0;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 5);

    while (i < resources_lost) {
        int to_remove = dist(rng);
        switch (to_remove) {
            case 1:
                if (player.caffeine_count == 0) continue;
                lost[Resources::CAFFEINE] += 1;
                player.caffeine_count--;
                break;
            case 2:
                if (player.lab_count == 0) continue;
                lost[Resources::LAB] += 1;
                player.lab_count--;
                break;
            case 3:
                if (player.lecture_count == 0) continue;
                lost[Resources::LECTURE] += 1;
                player.lecture_count--;
                break;
            case 4:
                if (player.study_count == 0) continue;
                lost[Resources::STUDY] += 1;
                player.study_count--;
                break;
            case 5:
                if (player.tutorial_count == 0) continue;
                lost[Resources::TUTORIAL] += 1;
                player.tutorial_count--;
                break;
        }

        i++;
    }
}

void Game_Controller::steal(int location) {
    const std::vector<Criterion *> criterions = board.get_tiles()[location]->get_criteria();

    string student_to_steal = "";
    vector<int> players_on_map(num_observers,0);
    int last_student = -1;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

    // make sure player has someone to steal from
    for (auto criterion : criterions) {
        if (criterion->get_player() != nullptr) {
            int idx = criterion->get_player()->idx;
            int total_resources = get_total_resources(idx);

            if (total_resources > 0 && idx != turn) {
                players_on_map[idx] += 1;
                last_student = MAX(last_student, idx);
            }
        }
    }

    if (last_student == -1) {
        cout << "Student " << p_list[turn]->name << " has no students to steal from.\n";
        return;
    }

    cout << "Student " << p_list[turn]->name << " can choose to steal from ";

    for (int i = 0; i < num_observers; i++) {
        if (players_on_map[i] > 0) {
            cout << p_list[i]->name;
            if (i != last_student) {
                cout << ", ";
            }
        }
    }

    cout << ".\n";

    cout << "Choose a student to steal from.\n";
    cout << '>';

    while (!(std::getline(cin, student_to_steal)) || !is_color(student_to_steal) || players_on_map[color_to_name(student_to_steal)] == 0) {
        if (cin.eof()) {
            save_game("backup.sv");
            exit(0);
        }
        cout << invalid_student << '\n';
        cin.clear();
        cout << '>';
    }

    Resources stolen;
    int idx = color_to_name(student_to_steal);
    double total = static_cast<double>(get_total_resources(idx));

    // distribution to generate numbers between 0 and 1 so that we can choose a resource to steal
    // based on the requirements
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double prob_caffeine = p_list[idx]->caffeine_count / total;
    double prob_lab = p_list[idx]->lab_count / total + prob_caffeine;
    double prob_lecture = p_list[idx]->lecture_count / total + prob_lab;
    double prob_study = p_list[idx]->study_count / total + prob_lecture;

    double rand = dis(gen);

    if (rand <= prob_caffeine) {
        p_list[turn]->caffeine_count += 1;
        p_list[idx]->caffeine_count -= 1;
        stolen = Resources::CAFFEINE;
    } else if (rand <= prob_lab) {
        p_list[turn]->lab_count += 1;
        p_list[idx]->lab_count -= 1;
        stolen = Resources::LAB;
    } else if (rand <= prob_lecture) {
        p_list[turn]->lecture_count += 1;
        p_list[idx]->lecture_count -= 1;
        stolen = Resources::LECTURE;
    } else if (rand <= prob_study) {
        p_list[turn]->study_count += 1;
        p_list[idx]->study_count -= 1;
        stolen = Resources::STUDY;
    } else {
        p_list[turn]->tutorial_count += 1;
        p_list[idx]->tutorial_count -= 1;
        stolen = Resources::TUTORIAL;
    }

    steal_output(idx, stolen);
}

void Game_Controller::steal_output(int loser, Resources resource) const {
    cout << "Student " << p_list[turn]->name << " steals " << ResourceToString(resource) << " from student " << p_list[loser]->name << ".\n";
}

int Game_Controller::get_total_resources(const int player_idx) const {
    return p_list[player_idx]->caffeine_count + p_list[player_idx]->lab_count + p_list[player_idx]->lecture_count + p_list[player_idx]->study_count + p_list[player_idx]->tutorial_count;
}

void Game_Controller::save_game(const string &filename) const {
    std::ofstream ofs{filename};

    ofs << turn << '\n';
    for (int i = 0; i < num_observers; i++) {
        output_player(ofs, i);
    }
    output_board(ofs);
    ofs << board.get_goose()->get_pos();
    ofs << '\n';
}

void Game_Controller::output_player(std::ostream &out, const int idx) const {
    // output number of resources for player
    out << p_list[idx]->caffeine_count << " " << p_list[idx]->lab_count << " " << p_list[idx]->lecture_count << " "
    << p_list[idx]->study_count << " " << p_list[idx]->tutorial_count << " g ";

    // output owned goals
    for (const auto &goal : p_list[idx]->owned_goal) {
        out << goal << " ";
    }
    out << "c";
    //output owned criterions

    int len = p_list[idx]->owned_criterions.size();
    int i = 0;
    if (len > 0) out << " ";
    for (const auto &criterion: p_list[idx]->owned_criterions) {
        if (i != len - 1) {
            out << criterion << " " << board.get_criteria()[criterion]->get_level() + 1 << " ";
        }
        else {
            out << criterion << " " << board.get_criteria()[criterion]->get_level() + 1;
        }
        i++;
    }
    out << '\n';
}

void Game_Controller::output_board(std::ostream &out) const {
    for (int i = 0; i < MAX_TILES; i++) {
        int resource_val = ResourceToNum(board.get_tiles()[i]->get_resource());
        int roll_val = board.get_tiles()[i]->get_roll_val();
        out << resource_val << " " << roll_val;
        if (i != MAX_TILES - 1) {
            out << " ";
        }
    }
    out << '\n';
}

void Game_Controller::load_player(const string &data, int idx) {
    std::istringstream iss{data};

    Player &p = *p_list[idx];

    string curr = "";

    iss >> p.caffeine_count >> p.lab_count >> p.lecture_count >> p.study_count
    >> p.tutorial_count;

    iss >> curr >> curr;

    while (std::isdigit(curr[0])) {
        p.owned_goal.insert(std::stoi(curr));
        board.get_goals()[std::stoi(curr)]->set_player(&p);
        string display = string{p.color} + "A";
        board.get_goals()[std::stoi(curr)]->set_display(display);
        iss >> curr;
    }

    while (iss >> curr) {
        int curr_criterion = std::stoi(curr);
        p.owned_criterions.insert(curr_criterion);
        board.get_criteria()[curr_criterion]->set_player(&p);

        iss >> curr;
        int level = std::stoi(curr) - 1;

        string display = string(1, p.color) + level_to_building(level);
        board.get_criteria()[curr_criterion]->set_display(display);

        p.points += level + 1;
        board.get_criteria()[curr_criterion]->set_level(level);
    }
}
