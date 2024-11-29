#include "subject.h"
#include "player.h"

void Subject::attach(std::unique_ptr<Player> observer) {
    p_list.emplace_back(std::move(observer));
    ++num_observers;
}

void Subject::detach(Player *observer) {
    for (auto it = p_list.begin(); it != p_list.end();) {
        if ((*it).get() == observer) {
            it = p_list.erase(it);
        }
        else {
            ++it;
        }
    }
    --num_observers;
}

void Subject::notifyObservers() {
    for (const auto &player :p_list) {
        player->notify();
    }
}

Subject::~Subject() {}
