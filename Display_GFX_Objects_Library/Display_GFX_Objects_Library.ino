#include "SPI.h"
#include "ILI9341_t3.h"

#include "drawIt.h"

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
#define GREY     0x5AEB

#define TFT_DC  9
#define TFT_CS 10

/*
   Using Hardware SPI!
   Just create the Display object like following. Then you can place any object you want on this screen
*/

ILI9341_t3 display(TFT_CS, TFT_DC);

void setup() {
  display.begin();
  display.setRotation(0);
  display.fillScreen(WHITE);
  
  drawIt::slider slider(display);
}

void loop() {
  
}
