#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "drawIt.h"

#define DRAWIT_BLACK    0x0000
#define DRAWIT_BLUE     0x001F
#define DRAWIT_RED      0xF800
#define DRAWIT_GREEN    0x07E0
#define DRAWIT_CYAN     0x07FF
#define DRAWIT_MAGENTA  0xF81F
#define DRAWIT_YELLOW   0xFFE0
#define DRAWIT_WHITE    0xFFFF
#define DRAWIT_GREY     0x5AEB

#define TFT_DC   4
#define TFT_CS   15
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK  13
#define TFT_RST  3
#define TFT_LED  20

#define delayx 20

/*
   Using Hardware SPI
*/

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

drawIt::slider slider(display);

void setup() {
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  
  display.begin();
  display.setRotation(0);
  display.fillScreen(DRAWIT_WHITE);

  slider.autoDraw(false);
  slider.changeOrigin(5, 5);
  slider.changeLength(50, 200);
  slider.setValue(.0);
  slider.autoDraw(true);
  
}

void loop() {
  //up
  for(int i = 0; i < 100; i+=5){
    slider.setValue(i/100.0);
    delay(delayx);
  }

  //down
  for(int i = 100; i > 0; i-=5){
    slider.setValue(i/100.0);
    delay(delayx);
  }
}
