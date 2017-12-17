#include "Arduino.h"
#include "SPI.h"
#include "TFT_ILI9341.h"
#include "drawIt.h"

drawIt::slider::slider(TFT_ILI9341 display, int x_origin, int y_origin, int x_length, int y_length, float value, bool touch){
  _display = display;
  this->changeOrigin(x_origin, y_origin);
  this->changeLength(x_length, y_length);
  this->setValue(value);
  this->setTouch(touch);

  return;
}

void drawIt::slider::changeOrigin(int x_origin, int y_origin){
  int _x_origin = x_origin, _y_origin = y_origin;
  return;
}

void drawIt::slider::changeLength(int x_length, int y_length){
  int _x_length = x_length, _y_length = y_length;
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
  this->getValue();
  return;
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
  this->getTouch();
  return;
}

