#pragma once

#include "touchArea.h"

namespace drawIt {

touchArea::touchArea(uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length, bool touchActivated) {
    this->changeOrigin(x_origin, y_origin);
    this->changeLength(x_length, y_length);
    this->setTouch(touchActivated);
}

bool touchArea::touched(uint16_t x, uint16_t y) {
    if (this->_touch && (x >= this->_origin.x) && (y >= this->_origin.y) && (x < (this->_origin.x + this->_length.x)) && (y < (this->_origin.y + this->_length.y)))
        return true;
    else
        return false;
}

}  // namespace drawIt