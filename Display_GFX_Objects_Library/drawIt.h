/*
   This is a simple library with basic display elements.

   Please specify your Display Object type below, decomment the one you using
*/

//#define _displayObjectType TFT_ILI9341      //for the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#define _displayObjectType ILI9341_t3         //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)
//#define _displayObjectType Adafruit_ILI9341 //for the original Adafruit_ILI9341 library

//#define _displayObjectType   //Or just put in our own (include it in the drawIt.h and drawIt.cpp!!!)
//you can basically use every library using the commands from Adafruit GFX

/*
   You will find the type of your display in the discription of your display library

   Now following include your display specific library
*/

//#include "TFT_ILI9341.h" //for the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#include "ILI9341_t3.h"    //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)

//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h" //These both for the original Adafruit GFX library with ILI9341 display

/*
   Now also include this .h file in the drawIt.cpp file of this library.

   Now if you have done all, start write your own code!
*/

//---------------------------------------------------------------------------------------------------------

#ifndef drawIt_h
#define drawIt_h

#include "Arduino.h"
#include "SPI.h"

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
#define GREY     0x5AEB

const uint16_t  _background    = WHITE,
                _outline       = BLACK,
                _slider        = WHITE,
                _slideroutline = BLACK;


class drawIt
{
  public:

    class slider {
      public:
        slider(_displayObjectType& _dsp);

        void changeOrigin(uint16_t x_origin, uint16_t y_origin); //
        void changeLength(uint16_t x_length, uint16_t y_length); //

        void setValue(float value); //
        void value(float value); //

        float getValue(); //
        float value(); //

        void setTouch(bool activated); //
        void touch(bool activated); //

        bool getTouch(); //
        bool touch(); //

        void touched(uint16_t x, uint16_t y);

        void setVisibility(bool visible); //
        void visible(bool visible); //

        bool getVisibility(); //
        bool visible(); //

        void autoDraw(bool active);
        bool autoDraw();

        void draw();

      private:
        _displayObjectType& _display;

        struct _origin {
          uint16_t x, y;
        } _origin;

        struct _length {
          uint16_t x, y;
        } _length;

        float _value;
        bool _touch, _visible, _autoDraw;

        struct _color {
          uint16_t background = _background, outline = _outline, slider = _slider, slideroutline = _slideroutline;
        } _color;
    };


    class button {
      public:

      private:

    };
};

#endif
