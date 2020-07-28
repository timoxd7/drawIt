#include "../src/drawIt.h"
#include "Arduino.h"
#include "ILI9341_t3.h"
#include "XPT2046_Touchscreen.h"
#include "font_Arial.h"

// Modify the following lines to match your hardware
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 6
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13

//And also the Touch-Pins for the XPT2046
#define TOUCH_CS 8
#define TOUCH_IRQ 2

#define delayx 20

/*
   Using Hardware SPI
*/

typedef ILI9341_t3 D;

ILI9341_t3 display = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_CLK, TFT_MISO);
//Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_CLK, TFT_MISO);

XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

const uint16_t slider_x_length = 50, slider_y_length = 310,
               button_x_length = 100, button_y_length = 100;

drawIt::slider<D> slider[2] = drawIt::slider<D>(display);
drawIt::button<D> button[2] = drawIt::button<D>(display);

void setup() {
    display.begin();
    display.setRotation(0);
    display.setFont(Arial_8);
    display.fillScreen(DRAWIT_WHITE);

    slider[0].changeOrigin(5, 5);
    slider[1].changeOrigin(60, 5);

    button[0].changeOrigin(115, 5);
    button[1].changeOrigin(115, 110);

    for (int i = 0; i < 2; i++) {
        slider[i].changeLength(slider_x_length, slider_y_length);
        slider[i].autoDraw(true);

        button[i].changeLength(button_x_length, button_y_length);
        button[i].autoDraw(true);
    }

    display.setTextColor(DRAWIT_BLACK);

    touch.begin(display.width(), display.height(), touch.getEEPROMCalibration());

    char buf[15];
    for (int i = 0; i < 2; i++) {
        snprintf(buf, sizeof(buf), "Slider %i at %i%%", i + 1, (uint8_t)(slider[i].getValue() * 100));
        display.setCursor(115, 235 + (i * 10));
        display.print(buf);
    }

    display.setCursor(115, 265);
    display.fillRect(110, 265, 130, 8, DRAWIT_WHITE);
    display.print("Pressure 0");
}

void loop() {
    static bool touched = true;

    if (touch.touched()) {
        touched = true;

        TS_Point p = touch.getPixel();

        for (int i = 0; i < 2; i++) {
            if (slider[i].touched(p.x, p.y)) {
                display.fillRect(110, 215, 130, 10, DRAWIT_WHITE);
                display.fillRect(110, 235 + (i * 10), 130, 8, DRAWIT_WHITE);

                char buf[17];

                snprintf(buf, sizeof(buf), "Slider %i touched", i + 1);
                display.setCursor(115, 215);
                display.print(buf);

                snprintf(buf, sizeof(buf), "Slider %i at %i%%", i + 1, (uint8_t)(slider[i].getValue() * 100));
                display.setCursor(115, 235 + (i * 10));
                display.print(buf);
            }
        }

        for (int i = 0; i < 2; i++) {
            if (button[i].touched(p.x, p.y)) {
                display.fillRect(110, 215, 130, 10, DRAWIT_WHITE);

                char buf[17];
                snprintf(buf, sizeof(buf), "Button %i touched", i + 1);
                display.setCursor(115, 215);
                display.print(buf);
            }
        }

        char buf[14];
        snprintf(buf, sizeof(buf), "Pressure %i", p.z);
        display.setCursor(115, 265);
        display.fillRect(110, 265, 130, 8, DRAWIT_WHITE);
        display.print(buf);

        delay(delayx);
    } else if (touched) {
        touched = false;

        display.fillRect(110, 215, 130, 8, DRAWIT_WHITE);
        display.setCursor(115, 215);
        display.print("Nothing touched");

        display.fillRect(110, 265, 130, 8, DRAWIT_WHITE);
        display.setCursor(115, 265);
        display.print("Pressure 0");
    }
}
