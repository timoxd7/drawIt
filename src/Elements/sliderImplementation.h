#pragma once

#include "slider.h"

namespace drawIt {

template <class D>
slider<D>::slider(D& _dsp, uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length, bool autoDrawActivated, float value, bool touchActivated)
    : _display(_dsp) {
    this->autoDraw(autoDrawActivated);
    this->changeOrigin(x_origin, y_origin);
    this->changeLength(x_length, y_length);
    this->setValue(value);
    this->setTouch(touchActivated);
    this->setVisibility(true);
}

template <class D>
void slider<D>::setValue(float value) {
    if (value > 1.0) {
        _value = 1.0;
    } else if (value < 0) {
        _value = 0;
    } else {
        _value = value;
    }

    if (this->_autoDraw) this->drawOnlySlider();
}

template <class D>
float slider<D>::getValue() {
    return _value;
}

template <class D>
void slider<D>::setSliderBackgroundColor(uint16_t sliderBackgroundColor) {
    _sliderColor.background = sliderBackgroundColor;
}

template <class D>
uint16_t slider<D>::getSliderBackgroundColor() {
    return _sliderColor.background;
}

template <class D>
bool slider<D>::touched(uint16_t x, uint16_t y) {
    //Touch on the slider?
    if (this->_touch && this->_visible && (x >= this->_origin.x) && (y >= this->_origin.y) && (x <= (this->_origin.x + this->_length.x)) && (y <= (this->_origin.y + this->_length.y))) {  // clear...
        if (this->_length.x > this->_length.y) {                                                                                                                                           //Wich direction?
            //minimum = _length.y/2 = 0
            //maximum = _length.x - _length.y/2 = 1

            _value = (x - this->_origin.x - this->_length.y / 2.0) / (this->_length.x - this->_length.y) * 1.0;

            if (_value > 1)
                _value = 1.0;
            else if (_value < 0)
                _value = 0;
        } else if (this->_length.y > this->_length.x) {
            //minimum = _length.y - _length.x/2 = 0
            //maximum = _length.x/2 = 1

            _value = 1.0 - (y - this->_origin.y - this->_length.x / 2.0) / (this->_length.y - this->_length.x) * 1.0;

            if (_value > 1)
                _value = 1.0;
            else if (_value < 0)
                _value = 0;
        } else {  //If it isn't a slider but a box
            _value = 0.0;
        }

        if (this->_autoDraw) this->drawOnlySlider();

        return true;
    } else
        return false;
}

template <class D>
void slider<D>::draw() {
    if (this->_visible) {
        drawOnlySlider();

        //Outline/Background
        _display.drawRect(this->_origin.x, this->_origin.y, this->_length.x, this->_length.y, this->_color.outline);
    }
}

template <class D>
void slider<D>::drawOnlySlider() {
    if (this->_visible) {
        //Outline/Background
        _display.fillRect(this->_origin.x + 1, this->_origin.y + 1, this->_length.x - 2, this->_length.y - 2, this->_color.background);

        //Slider
        if (this->_length.x > this->_length.y) {  //Horizontal
            uint16_t _slide_length = (this->_length.x - 2) - (this->_length.y - 2),
                     _x_sliderposition = (this->_origin.x + 1) + (_slide_length * _value),
                     _y_sliderposition = this->_origin.y + 1,
                     _sliderbox_size = this->_length.y - 2;

            _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
            _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
        } else if (this->_length.x < this->_length.y) {  //Vertical
            uint16_t _slide_length = (this->_length.y - 2) - (this->_length.x - 2),
                     _y_sliderposition = (this->_origin.y + 1) + (_slide_length * (1 - _value)),
                     _x_sliderposition = this->_origin.x + 1,
                     _sliderbox_size = this->_length.x - 2;

            _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
            _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
        } else {  //Same Same but different
            _display.fillRect(this->_origin.x + 1, this->_origin.y + 1, this->_length.x - 2, this->_length.y - 2, _sliderColor.background);
            _display.drawRect(this->_origin.x + 1, this->_origin.y + 1, this->_length.x - 2, this->_length.y - 2, _sliderColor.outline);
        }
    }
}

}  // namespace drawIt