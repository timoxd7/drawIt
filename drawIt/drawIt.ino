#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

#include "drawIt.h"

#define TFT_DC   15
#define TFT_CS   10
#define TFT_RST  4
#define TFT_LED  19
//#define TFT_MOSI 11
//#define TFT_MISO 12
//#define TFT_CLK  13

#define TOUCH_CS  20
#define TOUCH_IRQ 21

#define delayx 20

/*
   Using Hardware SPI
*/

ILI9341_t3 display = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);
//ILI9341_t3 display = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_CLK, TFT_MISO);

XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);


const uint16_t origin = 0, x_length = 50, y_length = 310;

drawIt::slider slider[4](display);

void setup() {
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  
  display.begin();
  display.setRotation(0);
  display.fillScreen(DRAWIT_WHITE);

  slider[0].changeOrigin(5, 5);

  slider[1].changeOrigin(60, 5);

  slider[2].changeOrigin(115, 5);

  slider[3].changeOrigin(170, 5);

  for(int i = 0; i < 4; i++) {
    slider[i].changeLength(x_length, y_length);
    slider[i].autoDraw(true);
  }

  touch.begin(display.width(), display.height(), touch.getEEPROMCalibration());
}

void loop() {

  if(touch.touched()){
    TS_Point p = touch.getPixel();
    
    for (int i = 0; i < 4; i++){
      slider[i].touched(p.x, p.y);
    }

    delay(delayx);
  }


/*
  //slider higher
  for(int i = 0; i <= 100; i+=5){
    slider[0].setValue(i/100.0);
    slider[1].setValue(i/200.0);
    slider[2].setValue(i/400.0);
    slider[3].setValue(i/800.0);
    delay(delayx);
  }

  //slider lower
  for(int i = 100; i >= 0; i-=5){
    slider[0].setValue(i/100.0);
    slider[1].setValue(i/200.0);
    slider[2].setValue(i/400.0);
    slider[3].setValue(i/800.0);
    delay(delayx);
  }

*/
  
/*
  //transition to horizontal
  for(int i = 0; i <= 100; i+=5){
    display.fillScreen(DRAWIT_WHITE);
    slider.changeLength(50 + (1.8 * i), 310 - (2.6 * i));
  }


  //slider higher
  for(int i = 0; i <= 100; i+=5){
    slider.setValue(i/100.0);
    delay(delayx);
  }

  //slider lower
  for(int i = 100; i >= 0; i-=5){
    slider.setValue(i/100.0);
    delay(delayx);
  }


  //transition to vertikal
  for(int i = 100; i >= 0; i = i-=5){
    display.fillScreen(DRAWIT_WHITE);
    slider.changeLength(50 + (1.8 * i), 310 - (2.6 * i));
  }
  */
}
