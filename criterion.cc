#include "criterion.h"

Criterion::Criterion(int pos): Asset(pos), tile{nullptr} {}

Tile *Criterion::get_tile() {return tile;}

void Criterion::set_tile(Tile *t) {tile = t;}
