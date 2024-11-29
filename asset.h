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

        // get position on board
        int get_pos();

        // get value displayed in View
        std::string get_display();

        // returns a nulllptr if building has no owner
        const Player *get_player() const;

        // according to invariance, every building has a tile, so the function returns a
        // pointer to a valid tile the building is found on
        Tile *get_tile() const;

        // setters for private fields
        void set_display(std::string &s);
        void set_player(Player *player);
        void set_tile(Tile *t);
};

#endif
