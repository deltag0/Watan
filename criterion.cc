#include "criterion.h"

Criterion::Criterion(int pos): Asset(pos) {}

Tile *Criterion::get_tile() const {return tile;}

void Criterion::set_tile(Tile *t) {tile = t;}

int Criterion::get_level() const {return level;}

void Criterion::increase_level() {++level;}

void Criterion::set_level(int l) {level = l;}

bool Criterion::in_the_way(const Player *player) const {
    if (owner == nullptr || owner == player) return false;

    return true;
}