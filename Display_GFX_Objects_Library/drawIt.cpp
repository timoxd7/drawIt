#include "Arduino.h"
#include "SPI.h"
#include "TFT_ILI9341.h"
#include "drawIt.h"

drawIt::slider::slider(TFT_ILI9341 display){
  _display = display;
  this->changeOrigin(0, 0);
  this->changeLength(0, 0);
  this->setValue(0.0);
  this->setTouch(true);
  this->setVisibility(true);

  return;
}

void drawIt::slider::changeOrigin(int x_origin, int y_origin){
  int _x_origin = x_origin, _y_origin = y_origin;
  return;
}

void drawIt::slider::changeLength(int x_length, int y_length){
  if(x_length >= 4 && y_length >= 4){
    _x_length = x_length, _y_length = y_length;
  } else {
    _x_length = 4, _y_length = 4;
  }
  
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

void drawIt::slider::touched(int x, int y){
  
}

void drawIt::slider::setVisibility(bool visible){
  _visible = visible;
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

void drawIt::slider::draw(){
  
}

//-----------------------------------------------------------------------------------------------


