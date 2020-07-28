#pragma once

namespace drawIt {

class touchArea : public drawIt_intern::position, public drawIt_intern::touch {
   public:
    touchArea(uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0, bool touchActivated = true);

    bool touched(uint16_t x, uint16_t y);
};

}  // namespace drawIt

#include "touchAreaImplementation.h"