#include "asset.h"

Asset::Asset(int pos) : pos{pos}, tile{nullptr}, owner{nullptr} {display = (pos < 10) ? (" " + std::to_string(pos)) : std::to_string(pos);}

Asset::~Asset() {}

int Asset::get_pos() {return pos;}

std::string Asset::get_display() {return display;}

const Player *Asset::get_player() const {return owner;}

void Asset::set_display(std::string &s) {display = s;}

void Asset::set_player(Player *player) {owner = player;}