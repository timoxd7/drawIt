#pragma once

#include "position.h"

namespace drawIt_intern {

class visuals : public position {
   public:
    void changeOrigin(uint16_t x_origin, uint16_t y_origin);  //
    void changeLength(uint16_t x_length, uint16_t y_length);  //

    void setVisibility(bool visible);  //

    bool getVisibility() {
        return _visible;
    }

    void autoDraw(bool active);
    bool autoDraw() {
        return _autoDraw;
    }

    virtual void draw() = 0;

   protected:
    bool _visible, _autoDraw;
};

}  // namespace drawIt_intern

#include "visualsImplementation.h"