#pragma once

namespace drawIt {

template <class D>
class button : public drawIt_intern::visuals, public drawIt_intern::touch, public drawIt_intern::color {
   public:
    button(D& _display, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0);

    bool touched(uint16_t x, uint16_t y);
    void draw();

   protected:
    D& _display;
};

}  // namespace drawIt

#include "buttonImplementation.h"