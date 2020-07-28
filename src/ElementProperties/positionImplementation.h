#pragma once

#include "position.h"

namespace drawIt_intern {

void position::changeOrigin(uint16_t x_origin, uint16_t y_origin) {
    _origin.x = x_origin, _origin.y = y_origin;
}

void position::changeLength(uint16_t x_length, uint16_t y_length) {
    if (x_length >= 4 && y_length >= 4) {
        _length.x = x_length, _length.y = y_length;
    } else {
        _length.x = 4, _length.y = 4;
    }
}

}  // namespace drawIt_intern