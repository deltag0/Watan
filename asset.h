#ifndef ASSET_H
#define ASSET_H

#include <string>


// Board Asset abstract class
// super class for Criterion and Goal
class Asset {
    protected:
        int pos;
        std::string display; // value displayed on the board for the asset
        bool is_captured = false;

    public:
        Asset(int pos);
        virtual ~Asset() = 0;
        int get_pos();
        std::string get_display();
};

#endif
