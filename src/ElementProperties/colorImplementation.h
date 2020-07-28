#pragma once

#include "color.h"

namespace drawIt_intern {

void color::setBackgroundColor(uint16_t backgroundColor) {
    _color.background = backgroundColor;
}

void color::setOutlineColor(uint16_t outlineColor) {
    _color.outline = outlineColor;
}

}  // namespace drawIt_intern