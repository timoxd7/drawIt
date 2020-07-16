/*
   This is a simple library with basic display elements.

   Please specify your Display Object-type below, decomment the one you want to use
*/

//#define _displayObjectType TFT_ILI9341      //For the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#define _displayObjectType ILI9341_t3         //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)
//#define _displayObjectType Adafruit_ILI9341 //For the original Adafruit_ILI9341 library

//#define _displayObjectType   //Or just put in our own
//you can basically use every library using the commands from Adafruit GFX

/*
   You will find the type of your display in the discription of your display library

   Now following include your display specific library
*/

//#include "TFT_ILI9341.h" //For the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#include "ILI9341_t3.h"    //For the obtimised ILI9341 library [for the teensy 3.2] (by Paul Stoffregen)

//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h" //These both for the original Adafruit GFX library with ILI9341 display

//#include <> //Or just put in your own library

/*
   Now if you have all done, start write your own code! :)
*/






//-----------------------------------------------------------------------------------------------------

//User Errors

//-----------------------------------------------------------------------------------------------------

#ifndef _displayObjectType
#error "You have to specify an object-type in the drawIt.h !"
#endif //_displayObjectType


//-----------------------------------------------------------------------------------------------------

//Library inclusions and color definitions

//-----------------------------------------------------------------------------------------------------

#ifndef drawIt_h
#define drawIt_h

#include "Arduino.h"
#include "SPI.h"

#define DRAWIT_BLACK    0x0000
#define DRAWIT_BLUE     0x001F
#define DRAWIT_RED      0xF800
#define DRAWIT_GREEN    0x07E0
#define DRAWIT_CYAN     0x07FF
#define DRAWIT_MAGENTA  0xF81F
#define DRAWIT_YELLOW   0xFFE0
#define DRAWIT_WHITE    0xFFFF
#define DRAWIT_GREY     0x5AEB


//-----------------------------------------------------------------------------------------------------

//Classes

//-----------------------------------------------------------------------------------------------------

class drawIt
{
  private:

    class visuals {
      public:

        void changeOrigin(uint16_t x_origin, uint16_t y_origin); //
        void changeLength(uint16_t x_length, uint16_t y_length); //

        void setVisibility(bool visible); //

        bool getVisibility() {
          return _visible;
        }

        void autoDraw(bool active);
        bool autoDraw() {
          return _autoDraw;
        }
        
        virtual void draw();

      protected:

        struct _origin {
          uint16_t x, y;
        } _origin;

        struct _length {
          uint16_t x, y;
        } _length;

        bool _visible, _autoDraw;
    };


    class touch {
      public:

        virtual bool touched(uint16_t x, uint16_t y); //

        void setTouch(bool activated){
          _touch = activated;
        }

        bool getTouch(){
          return _touch;
        }

      protected:

        bool _touch;
    };


    class color {
      public:

        void setBackgroundColor(uint16_t backgroundColor);

        uint16_t getBackgroundColor() {
          return _color.background;
        }

        void setOutlineColor(uint16_t outlineColor);

        uint16_t getOutlineColor() {
          return _color.outline;
        }

      protected:
        struct _color {
          uint16_t background = DRAWIT_WHITE, outline = DRAWIT_BLACK;
        } _color;
    };


  public:

    class slider : public visuals, public touch, public color {
      public:
        slider(_displayObjectType& _display, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0, bool autoDrawActivated = false, float value = 0.0, bool touchActivated = true); //

        void setValue(float value); //

        float getValue(); //

        bool touched(uint16_t x, uint16_t y);

        void setSliderBackgroundColor(uint16_t sliderBackgroundColor);

        uint16_t getSliderBackgroundColor();

        void draw(); //

      protected:
        _displayObjectType& _display;

        float _value;

        struct _sliderColor {
          uint16_t background = DRAWIT_WHITE, outline = DRAWIT_BLACK;
        } _sliderColor;
    };


    class button : public visuals, public touch, public color {
      public:
        button(_displayObjectType& _display, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0, bool autoDrawActivated = false, bool touchActivated = true);

        bool touched(uint16_t x, uint16_t y);
        void draw();

      protected:
        _displayObjectType& _display;
    };
};

#endif //drawIt_h
