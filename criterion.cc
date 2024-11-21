#include "criterion.h"

Criterion::Criterion(int pos): Asset(pos) {}

Tile *Criterion::get_tile() {return tile;}

void Criterion::set_tile(Tile *t) {tile = t;}

bool Criterion::in_the_way(const Player *player) const {
    if (owner == nullptr || owner == player) return false;

    return true;
}