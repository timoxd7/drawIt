/*
 * Here you have to include the .h file of your display library.
 * Or just decomment one if it's the right one you already need.
 */

//#include "TFT_ILI9341.h" //for the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#include "ILI9341_t3.h"    //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)

//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h" //These both for the original Adafruit GFX library with ILI9341 display

/*
 * Now just have a look at the instructions in the drawIt.h file.
 * Then you can start coding in the .ino file of your project!
 */

//-----------------------------------------------------------------------------------------------------


#include "Arduino.h"
#include "SPI.h"
#include "drawIt.h"


drawIt::slider::slider(_displayObjectType& _dsp): _display(_dsp){
  this->autoDraw(false);
  this->changeOrigin(0, 0);
  this->changeLength(0, 0);
  this->setValue(0.0);
  this->setTouch(true);
  this->setVisibility(true);

  return;
}

void drawIt::slider::changeOrigin(uint16_t x_origin, uint16_t y_origin){
  _x_origin = x_origin, _y_origin = y_origin;

  if(_autoDraw) this->draw();
  return;
}

void drawIt::slider::changeLength(uint16_t x_length, uint16_t y_length){
  if(x_length >= 4 && y_length >= 4){
    _x_length = x_length, _y_length = y_length;
  } else {
    _x_length = 4, _y_length = 4;
  }

  if(_autoDraw) this->draw();
  return;
}

void drawIt::slider::setValue(float value){
  if(value > 1.0) {
    _value = 1.0;
  } else if (value < 0) {
    _value = 0;
  } else {
    _value = value;
  }

  if(_autoDraw) this->draw();
  return;
}

void drawIt::slider::value(float value){
  this->setValue(value);
  return;
}

float drawIt::slider::getValue(){
  return _value;
}

float drawIt::slider::value() {
  return this->getValue();
}

void drawIt::slider::setTouch(bool activated){
  _touch = activated;
  return;
}

void drawIt::slider::touch(bool activated){
  this->setTouch(activated);
  return;
}

bool drawIt::slider::getTouch(){
  return _touch;
}

bool drawIt::slider::touch(){
  return this->getTouch();
}

void drawIt::slider::touched(uint16_t x, uint16_t y){
  //Touch on the slider?
  if((x > _x_origin+1) && (y > _y_origin+1) && (x < (_x_origin+_x_length-2)) && (y < (_y_origin+_y_length-2))){ // clear...
    if(_x_length > _y_length){ //Wich direction?
      if(x < ((_x_origin+1) + ((_y_length-2)/2))){ //Minimum?
        _value = 0.0;
      } else if (x > ((_x_origin + _x_length-1) - ((_y_length-2)/2))) { //Maximum?
        _value = 1.0;
      } else { //between
        _value = (x - (_x_origin+1 + ((_y_length-2)/2))) / ((_x_length-2) - (_y_length-2)) * 1.0;
      }
    } else if(_y_length > _x_length){
      if(y < ((_y_origin+1) + ((_x_length-2)/2))){ //Now Maximum?
        _value = 1.0;
      } else if (y > ((_y_origin + _y_length-1) - ((_x_length-2)/2))) { //Now Minimum?
        _value = 0.0;
      } else { //between
        _value = 1.0 - ((y - (_y_origin+1 + ((_x_length-2)/2))) / ((_y_length-2) - (_x_length-2)) * 1.0);
      }
    } else { //If it isn't a slider but a box
      _value = 0.0;
    }
    
    if(_autoDraw) this->draw();
  }
  
  return;
}

void drawIt::slider::setVisibility(bool visible){
  _visible = visible;
  
  if(_autoDraw) this->draw();
  return;
}

void drawIt::slider::visible(bool visible){
  this->setVisibility(visible);
  return;
}

bool drawIt::slider::getVisibility(){
  return _visible;
}

bool drawIt::slider::visible(){
  return this->getVisibility();
}

void drawIt::slider::autoDraw(bool active){
  _autoDraw = active;

  if(_autoDraw) this->draw();
  return;
}

void drawIt::slider::draw(){
  if(_visible){
    //Outline/Background
    _display.fillRect(_x_origin, _y_origin, _x_length, _y_length, _color.background);
    _display.drawRect(_x_origin, _y_origin, _x_length, _y_length, _color.outline);

    //Slider
    if(_x_length > _y_length){
      uint16_t _slide_length = _x_length - (_y_length -2);
      uint16_t _x_sliderposition = (_x_origin+1) + (_slide_length*_value);
      uint16_t _sliderbox_size = _y_length -2;
      
      _display.fillRect(_x_sliderposition, _y_origin + 1, _sliderbox_size, _sliderbox_size, _color.slider);
      _display.drawRect(_x_sliderposition, _y_origin + 1, _sliderbox_size, _sliderbox_size, _color.slideroutline);
    } else if(_x_length < _y_length){
      uint16_t _slide_length = _y_length - (_x_length -2);
      uint16_t _y_sliderposition = (_y_origin+1) + (_slide_length*(1 - _value));
      uint16_t _sliderbox_size = _x_length -2;
      
      _display.fillRect(_x_origin + 1, _y_sliderposition, _sliderbox_size, _sliderbox_size, _color.slider);
      _display.drawRect(_x_origin + 1, _y_sliderposition, _sliderbox_size, _sliderbox_size, _color.slideroutline);
    } else {
      _display.fillRect(_x_origin+1, _y_origin+1, _x_length-2, _y_length-2, _color.slider);
      _display.drawRect(_x_origin+1, _y_origin+1, _x_length-2, _y_length-2, _color.slideroutline);
    }
  }
}

//-----------------------------------------------------------------------------------------------


