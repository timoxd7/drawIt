#pragma once

#include "visuals.h"

namespace drawIt_intern {

void visuals::changeOrigin(uint16_t x_origin, uint16_t y_origin) {
    position::changeOrigin(x_origin, y_origin);

    if (_autoDraw) this->draw();
}

void visuals::changeLength(uint16_t x_length, uint16_t y_length) {
    position::changeLength(x_length, y_length);

    if (_autoDraw) this->draw();
}

void visuals::setVisibility(bool visible) {
    _visible = visible;

    if (_autoDraw) this->draw();
}

void visuals::autoDraw(bool active) {
    _autoDraw = active;

    if (_autoDraw) this->draw();
}

}  // namespace drawIt_intern