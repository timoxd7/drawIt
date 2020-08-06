/*
   This is a simple library with basic display elements.

   Specify your Display Type by the Template

   Tested with:

   TFT_ILI9341      //For the ILI9341 optimised libary ONLY FOR AVR PROCESSORS (by Bodmer)
   ILI9341_t3       //For the obtimised ILI9341 library for the teensy (by Paul Stoffregen)
   Adafruit_ILI9341 //For the original Adafruit_ILI9341 library
*/


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

// ElementProperties
#include "ElementProperties/position.h"
#include "ElementProperties/visuals.h"
#include "ElementProperties/color.h"
#include "ElementProperties/touch.h"

// Elements
#include "Elements/button.h"
#include "Elements/slider.h"
#include "Elements/touchArea.h"
#include "Elements/staticLabel.h"


#endif  //drawIt_h
