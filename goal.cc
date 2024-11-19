#include "goal.h"

Goal::Goal(int pos) : Asset(pos), tile{nullptr} {}

Tile *Goal::get_tile() {return tile;}

void Goal::set_tile(Tile *t) {tile = t;}
