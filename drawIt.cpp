#include "drawIt.h"


//-----------------------------------------------------------------------------------------------------

//Visuals

//-----------------------------------------------------------------------------------------------------

void drawIt::visuals::changeOrigin(uint16_t x_origin, uint16_t y_origin) {
  _origin.x = x_origin, _origin.y = y_origin;

  if (_autoDraw) this->draw();
}

void drawIt::visuals::changeLength(uint16_t x_length, uint16_t y_length) {
  if (x_length >= 4 && y_length >= 4) {
    _length.x = x_length, _length.y = y_length;
  } else {
    _length.x = 4, _length.y = 4;
  }

  if (_autoDraw) this->draw();
}

void drawIt::visuals::setVisibility(bool visible) {
  _visible = visible;

  if (_autoDraw) this->draw();
}

void drawIt::visuals::autoDraw(bool active) {
  _autoDraw = active;

  if (_autoDraw) this->draw();
}


//-----------------------------------------------------------------------------------------------------

//Color

//-----------------------------------------------------------------------------------------------------

void drawIt::color::setBackgroundColor(uint16_t backgroundColor) {
  _color.background = backgroundColor;
}

void drawIt::color::setOutlineColor(uint16_t outlineColor) {
  _color.outline = outlineColor;
}


//-----------------------------------------------------------------------------------------------------

//Basic Slider

//-----------------------------------------------------------------------------------------------------

drawIt::slider::slider(_displayObjectType& _dsp, uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length, bool autoDrawActivated, float value, bool touchActivated)
  : _display(_dsp) {
  this->autoDraw(autoDrawActivated);
  this->changeOrigin(x_origin, y_origin);
  this->changeLength(x_length, y_length);
  this->setValue(value);
  this->setTouch(touchActivated);
  this->setVisibility(true);
}

void drawIt::slider::setValue(float value) {
  if (value > 1.0) {
    _value = 1.0;
  } else if (value < 0) {
    _value = 0;
  } else {
    _value = value;
  }

  if (_autoDraw) this->draw();
}

float drawIt::slider::getValue() {
  return _value;
}

void drawIt::slider::setSliderBackgroundColor(uint16_t sliderBackgroundColor) {
  _sliderColor.background = sliderBackgroundColor;
}

uint16_t drawIt::slider::getSliderBackgroundColor() {
  return _sliderColor.background;
}

bool drawIt::slider::touched(uint16_t x, uint16_t y) {
  //Touch on the slider?
  if (_visible && (x >= _origin.x) && (y >= _origin.y) && (x <= (_origin.x + _length.x)) && (y <= (_origin.y + _length.y))) { // clear...
    if (_length.x > _length.y) { //Wich direction?
      //minimum = _length.y/2 = 0
      //maximum = _length.x - _length.y/2 = 1

      _value = (x - _origin.x - _length.y / 2.0) / (_length.x - _length.y) * 1.0;

      if (_value > 1) _value = 1.0; else if (_value < 0) _value = 0;
    } else if (_length.y > _length.x) {
      //minimum = _length.y - _length.x/2 = 0
      //maximum = _length.x/2 = 1

      _value = 1.0 - (y - _origin.y - _length.x / 2.0) / (_length.y - _length.x) * 1.0;

      if (_value > 1) _value = 1.0; else if (_value < 0) _value = 0;
    } else { //If it isn't a slider but a box
      _value = 0.0;
    }

    if (_autoDraw) this->draw();

    return true;
  } else return false;
}

void drawIt::slider::draw() {
  if (_visible) {
    //Outline/Background
    _display.fillRect(_origin.x, _origin.y, _length.x, _length.y, _color.background);
    _display.drawRect(_origin.x, _origin.y, _length.x, _length.y, _color.outline);

    //Slider
    if (_length.x > _length.y) { //Horizontal
      uint16_t _slide_length     = (_length.x - 2) - (_length.y - 2),
               _x_sliderposition = (_origin.x + 1) + (_slide_length * _value),
               _y_sliderposition = _origin.y + 1,
               _sliderbox_size   = _length.y - 2;

      _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
      _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
    } else if (_length.x < _length.y) { //Vertical
      uint16_t _slide_length     = (_length.y - 2) - (_length.x - 2),
               _y_sliderposition = (_origin.y + 1) + (_slide_length * (1 - _value)),
               _x_sliderposition = _origin.x + 1,
               _sliderbox_size   = _length.x - 2;

      _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
      _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
    } else { //Same Same but different
      _display.fillRect(_origin.x + 1, _origin.y + 1, _length.x - 2, _length.y - 2, _sliderColor.background);
      _display.drawRect(_origin.x + 1, _origin.y + 1, _length.x - 2, _length.y - 2, _sliderColor.outline);
    }
  }
}


//-----------------------------------------------------------------------------------------------------

//Basic Button

//-----------------------------------------------------------------------------------------------------

drawIt::button::button(_displayObjectType& _dsp, uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length, bool autoDrawActivated, bool touchActivated)
  : _display(_dsp) {
  this->autoDraw(autoDrawActivated);
  this->changeOrigin(x_origin, y_origin);
  this->changeLength(x_length, y_length);
  this->setTouch(touchActivated);
  this->setVisibility(true);
}

bool drawIt::button::touched(uint16_t x, uint16_t y) {
  if (_visible && (x >= _origin.x) && (y >= _origin.y) && (x <= (_origin.x + _length.x)) && (y <= (_origin.y + _length.y))) return true; else return false;
}

void drawIt::button::draw() {
  if (_visible) {
    //Outline/Background (all of the button)
    _display.fillRect(_origin.x, _origin.y, _length.x, _length.y, _color.background);
    _display.drawRect(_origin.x, _origin.y, _length.x, _length.y, _color.outline);
  }
}
