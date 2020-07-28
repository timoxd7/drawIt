#pragma once

namespace drawIt_intern {

class position {
   public:
    virtual void changeOrigin(uint16_t x_origin, uint16_t y_origin);  //
    virtual void changeLength(uint16_t x_length, uint16_t y_length);  //

   protected:
    struct _origin {
        uint16_t x, y;
    } _origin;

    struct _length {
        uint16_t x, y;
    } _length;
};

}  // namespace drawIt_intern

#include "positionImplementation.h"