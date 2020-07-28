#pragma once

namespace drawIt_intern {

class color {
   public:
    void setBackgroundColor(uint16_t backgroundColor);

    uint16_t getBackgroundColor() {
        return _color.background;
    }

    void setOutlineColor(uint16_t outlineColor);

    uint16_t getOutlineColor() {
        return _color.outline;
    }

   protected:
    struct _color {
        uint16_t background = DRAWIT_WHITE, outline = DRAWIT_BLACK;
    } _color;
};

}  // namespace drawIt_intern

#include "colorImplementation.h"