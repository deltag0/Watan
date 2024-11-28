#ifndef ASSET_H
#define ASSET_H

#include <string>

class Player;
class Tile;

// Board Asset abstract class
// super class for Criterion and Goal
class Asset {
    protected:
        int pos;
        std::string display; // value displayed on the board for the asset
        Tile *tile; // which tile the asset is on (always initialized)
        Player *owner; // player who owns the asset (nullptr if none)

    public:
        Asset(int pos);
        virtual ~Asset() = 0;
        int get_pos();
        std::string get_display();
        const Player *get_player() const;
        void set_display(std::string &s);
        void set_player(Player *player);
};

#endif
