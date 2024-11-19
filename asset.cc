#include "asset.h"

Asset::Asset(int pos) : pos{pos}, display{std::to_string(pos)}, tile{nullptr} {}

Asset::~Asset() {}

int Asset::get_pos() {return pos;}

std::string Asset::get_display() {return display;}
