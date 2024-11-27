#ifndef VIEW_H
#define VIEW_H

#include "board.h"

class View {
   public:
    virtual void display(Board &b) const = 0;
    virtual ~View() = default;
};

#endif
