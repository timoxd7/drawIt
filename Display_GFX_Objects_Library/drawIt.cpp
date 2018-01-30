/*
   Here you have to include the .h file of your display library.
   Or just decomment one if it's the right one you already need.
*/

//#include "TFT_ILI9341.h" //for the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#include "ILI9341_t3.h"    //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)

//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h" //These both for the original Adafruit GFX library with ILI9341 display

/*
   Now just have a look at the instructions in the drawIt.h file.
   Then you can start coding in the .ino file of your project!
*/

//-----------------------------------------------------------------------------------------------------


#include "Arduino.h"
#include "SPI.h"
#include "drawIt.h"


drawIt::slider::slider(_displayObjectType& _dsp, uint16_t x_origin, uint16_t y_origin, uint16_t x_length, uint16_t y_length, bool autoDrawActivated, float value, bool touchActivated)
  : _display(_dsp) {
  this->autoDraw(autoDrawActivated);
  this->changeOrigin(x_origin, y_origin);
  this->changeLength(x_length, y_length);
  this->setValue(value);
  this->setTouch(touchActivated);
  this->setVisibility(autoDrawActivated);

  return;
}

void drawIt::slider::changeOrigin(uint16_t x_origin, uint16_t y_origin) {
  _origin.x = x_origin, _origin.y = y_origin;

  if (_autoDraw) this->draw();
  return;
}

void drawIt::slider::changeLength(uint16_t x_length, uint16_t y_length) {
  if (x_length >= 4 && y_length >= 4) {
    _length.x = x_length, _length.y = y_length;
  } else {
    _length.x = 4, _length.y = 4;
  }

  if (_autoDraw) this->draw();
  return;
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
  return;
}

void drawIt::slider::value(float value) {
  this->setValue(value);
  return;
}

float drawIt::slider::getValue() {
  return _value;
}

float drawIt::slider::value() {
  return this->getValue();
}

void drawIt::slider::setTouch(bool activated) {
  _touch = activated;
  return;
}

void drawIt::slider::touch(bool activated) {
  this->setTouch(activated);
  return;
}

bool drawIt::slider::getTouch() {
  return _touch;
}

bool drawIt::slider::touch() {
  return this->getTouch();
}

void drawIt::slider::touched(uint16_t x, uint16_t y) {
  //Touch on the slider?
  if ((x > _origin.x + 1) && (y > _origin.y + 1) && (x < (_origin.x + _length.x - 2)) && (y < (_origin.y + _length.y - 2))) { // clear...
    if (_length.x > _length.y) { //Wich direction?
      if (x < ((_origin.x + 1) + ((_length.y - 2) / 2))) { //Minimum?
        _value = 0.0;
      } else if (x > ((_origin.x + _length.x - 1) - ((_length.y - 2) / 2))) { //Maximum?
        _value = 1.0;
      } else { //between
        _value = (x - (_origin.x + 1 + ((_length.y - 2) / 2))) / ((_length.x - 2) - (_length.y - 2)) * 1.0;
      }
    } else if (_length.y > _length.x) {
      if (y < ((_origin.y + 1) + ((_length.x - 2) / 2))) { //Now Maximum?
        _value = 1.0;
      } else if (y > ((_origin.y + _length.y - 1) - ((_length.x - 2) / 2))) { //Now Minimum?
        _value = 0.0;
      } else { //between
        _value = 1.0 - ((y - (_origin.y + 1 + ((_length.x - 2) / 2))) / ((_length.y - 2) - (_length.x - 2)) * 1.0);
      }
    } else { //If it isn't a slider but a box
      _value = 0.0;
    }

    if (_autoDraw) this->draw();
  }

  return;
}

void drawIt::slider::setVisibility(bool visible) {
  _visible = visible;

  if (_autoDraw) this->draw();
  return;
}

void drawIt::slider::visible(bool visible) {
  this->setVisibility(visible);
  return;
}

bool drawIt::slider::getVisibility() {
  return _visible;
}

bool drawIt::slider::visible() {
  return this->getVisibility();
}

void drawIt::slider::autoDraw(bool active) {
  _autoDraw = active;

  if (_autoDraw) this->draw();
  return;
}

void drawIt::slider::draw() {
  if (_visible) {
    //Outline/Background
    _display.fillRect(_origin.x, _origin.y, _length.x, _length.y, _color.background);
    _display.drawRect(_origin.x, _origin.y, _length.x, _length.y, _color.outline);

    //Slider
    if (_length.x > _length.y) {
      uint16_t _slide_length = (_length.x - 2) - (_length.y - 2);
      uint16_t _x_sliderposition = (_origin.x + 1) + (_slide_length * _value);
      uint16_t _sliderbox_size = _length.y - 2;

      _display.fillRect(_x_sliderposition, _origin.y + 1, _sliderbox_size, _sliderbox_size, _color.slider);
      _display.drawRect(_x_sliderposition, _origin.y + 1, _sliderbox_size, _sliderbox_size, _color.slideroutline);
    } else if (_length.x < _length.y) {
      uint16_t _slide_length = (_length.y - 2) - (_length.x - 2);
      uint16_t _y_sliderposition = (_origin.y + 1) + (_slide_length * (1 - _value));
      uint16_t _sliderbox_size = _length.x - 2;

      _display.fillRect(_origin.x + 1, _y_sliderposition, _sliderbox_size, _sliderbox_size, _color.slider);
      _display.drawRect(_origin.x + 1, _y_sliderposition, _sliderbox_size, _sliderbox_size, _color.slideroutline);
    } else {
      _display.fillRect(_origin.x + 1, _origin.y + 1, _length.x - 2, _length.y - 2, _color.slider);
      _display.drawRect(_origin.x + 1, _origin.y + 1, _length.x - 2, _length.y - 2, _color.slideroutline);
    }
  }
}

//-----------------------------------------------------------------------------------------------


