#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "view.h"

class TextView : public View {
   public:
    void display(Board &b) const override;
};

#endif
