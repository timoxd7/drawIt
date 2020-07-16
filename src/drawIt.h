/*
   This is a simple library with basic display elements.

   Please specify your Display Object-type below, decomment the one you want to use
*/

//#define _displayObjectType TFT_ILI9341      //For the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#define _displayObjectType ILI9341_t3  //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)
//#define _displayObjectType Adafruit_ILI9341 //For the original Adafruit_ILI9341 library

//#define _displayObjectType   //Or just put in our own
//you can basically use every library using the commands from Adafruit GFX

/*
   You will find the type of your display in the discription of your display library

   Now following include your display specific library
*/

//#include "TFT_ILI9341.h" //For the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
#include "ILI9341_t3.h"  //For the obtimised ILI9341 library [for the teensy 3.2] (by Paul Stoffregen)

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
#endif  //_displayObjectType


//-----------------------------------------------------------------------------------------------------

//Library inclusions and color definitions

//-----------------------------------------------------------------------------------------------------

#ifndef drawIt_h
#define drawIt_h

#include "Arduino.h"
#include "SPI.h"

#define DRAWIT_BLACK 0x0000
#define DRAWIT_BLUE 0x001F
#define DRAWIT_RED 0xF800
#define DRAWIT_GREEN 0x07E0
#define DRAWIT_CYAN 0x07FF
#define DRAWIT_MAGENTA 0xF81F
#define DRAWIT_YELLOW 0xFFE0
#define DRAWIT_WHITE 0xFFFF
#define DRAWIT_GREY 0x5AEB


//-----------------------------------------------------------------------------------------------------

//Classes

//-----------------------------------------------------------------------------------------------------

class drawIt {
   private:
    class visuals {
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
        virtual bool touched(uint16_t x, uint16_t y);  //

        void setTouch(bool activated) {
            _touch = activated;
        }

        bool getTouch() {
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
        slider(_displayObjectType& _display, uint16_t x_origin = 0, uint16_t y_origin = 0, uint16_t x_length = 0, uint16_t y_length = 0, bool autoDrawActivated = false, float value = 0.0, bool touchActivated = true);  //

        void setValue(float value);  //

        float getValue();  //

        bool touched(uint16_t x, uint16_t y);

        void setSliderBackgroundColor(uint16_t sliderBackgroundColor);

        uint16_t getSliderBackgroundColor();

        void draw();  //

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


// ------------------------- Implementation -------------------------


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
    if (_visible && (x >= _origin.x) && (y >= _origin.y) && (x <= (_origin.x + _length.x)) && (y <= (_origin.y + _length.y))) {  // clear...
        if (_length.x > _length.y) {                                                                                             //Wich direction?
            //minimum = _length.y/2 = 0
            //maximum = _length.x - _length.y/2 = 1

            _value = (x - _origin.x - _length.y / 2.0) / (_length.x - _length.y) * 1.0;

            if (_value > 1)
                _value = 1.0;
            else if (_value < 0)
                _value = 0;
        } else if (_length.y > _length.x) {
            //minimum = _length.y - _length.x/2 = 0
            //maximum = _length.x/2 = 1

            _value = 1.0 - (y - _origin.y - _length.x / 2.0) / (_length.y - _length.x) * 1.0;

            if (_value > 1)
                _value = 1.0;
            else if (_value < 0)
                _value = 0;
        } else {  //If it isn't a slider but a box
            _value = 0.0;
        }

        if (_autoDraw) this->draw();

        return true;
    } else
        return false;
}

void drawIt::slider::draw() {
    if (_visible) {
        //Outline/Background
        _display.fillRect(_origin.x, _origin.y, _length.x, _length.y, _color.background);
        _display.drawRect(_origin.x, _origin.y, _length.x, _length.y, _color.outline);

        //Slider
        if (_length.x > _length.y) {  //Horizontal
            uint16_t _slide_length = (_length.x - 2) - (_length.y - 2),
                     _x_sliderposition = (_origin.x + 1) + (_slide_length * _value),
                     _y_sliderposition = _origin.y + 1,
                     _sliderbox_size = _length.y - 2;

            _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
            _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
        } else if (_length.x < _length.y) {  //Vertical
            uint16_t _slide_length = (_length.y - 2) - (_length.x - 2),
                     _y_sliderposition = (_origin.y + 1) + (_slide_length * (1 - _value)),
                     _x_sliderposition = _origin.x + 1,
                     _sliderbox_size = _length.x - 2;

            _display.fillRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.background);
            _display.drawRect(_x_sliderposition, _y_sliderposition, _sliderbox_size, _sliderbox_size, _sliderColor.outline);
        } else {  //Same Same but different
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
    if (_visible && (x >= _origin.x) && (y >= _origin.y) && (x <= (_origin.x + _length.x)) && (y <= (_origin.y + _length.y)))
        return true;
    else
        return false;
}

void drawIt::button::draw() {
    if (_visible) {
        //Outline/Background (all of the button)
        _display.fillRect(_origin.x, _origin.y, _length.x, _length.y, _color.background);
        _display.drawRect(_origin.x, _origin.y, _length.x, _length.y, _color.outline);
    }
}

#endif  //drawIt_h
