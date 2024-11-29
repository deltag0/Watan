#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"

class TextView : public View {
   public:
    // displays entire board
    void display(Board &b) const override;
};

#endif
