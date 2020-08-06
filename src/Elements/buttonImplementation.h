#pragma once

#include "button.h"

namespace drawIt {

template <class D>
button<D>::button(D& _dsp, uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length)
    : _display(_dsp) {
    this->changeOrigin(x_origin, y_origin);
    this->changeLength(x_length, y_length);
    this->setVisibility(true);
}

template <class D>
bool button<D>::touched(uint16_t x, uint16_t y) {
    if (this->_touch && this->_visible && (x >= this->_origin.x) && (y >= this->_origin.y) && (x < (this->_origin.x + this->_length.x)) && (y < (this->_origin.y + this->_length.y)))
        return true;
    else
        return false;
}

template <class D>
void button<D>::draw() {
    if (this->_visible) {
        //Outline/Background (all of the button)
        _display.fillRect(this->_origin.x, this->_origin.y, this->_length.x, this->_length.y, this->_color.background);
        _display.drawRect(this->_origin.x, this->_origin.y, this->_length.x, this->_length.y, this->_color.outline);
    }
}

}  // namespace drawIt