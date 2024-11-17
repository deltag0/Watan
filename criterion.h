#ifndef CRITERION_H
#define CRITERION_H

#include <string>

#include "assets.h"

#define MAX_CRITERION 53

// 53 criterions on one board
class Criterion: public Asset {

    public:
        Criterion(int display);

};


#endif