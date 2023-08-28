#include <SPI.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

#define TFT_CS PA4
#define TFT_RST PA6
#define TFT_DC PB1
#define TFT_MOSI PA7
#define TFT_SCLK PA5


Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  tft.init(240, 240, 3);

  tft.fillScreen(ST77XX_MAGENTA);
  tft.fillScreen(ST77XX_GREEN);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Hello world");
  tft.setCursor(20, 20);
  tft.println("Hello world");
}

void loop() {
  
}