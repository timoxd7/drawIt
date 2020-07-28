#pragma once

namespace drawIt {

template <class D>
class slider : public drawIt_intern::visuals, public drawIt_intern::touch, public drawIt_intern::color {
   public:
    slider(D& _display, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0, bool autoDrawActivated = false, float value = 0.0, bool touchActivated = true);  //

    void setValue(float value);  //

    float getValue();  //

    bool touched(uint16_t x, uint16_t y);

    void setSliderBackgroundColor(uint16_t sliderBackgroundColor);

    uint16_t getSliderBackgroundColor();

    void draw();  //

   protected:
    D& _display;

    float _value;

    struct _sliderColor {
        uint16_t background = DRAWIT_WHITE, outline = DRAWIT_BLACK;
    } _sliderColor;

    void drawOnlySlider();
};

}  // namespace drawIt

#include "sliderImplementation.h"