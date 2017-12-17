#include "SPI.h"
#include "TFT_ILI9341.h"

#include "drawIt.h"

/*
   Using Hardware SPI!
   Just create the Display object like following. Then you can place any object you want on this screen
*/

TFT_ILI9341 display = TFT_ILI9341();

void setup() {
  drawIt::slider slider(display, 0, 0, 0, 0, 0.0, true);
}

void loop() {
  
}
