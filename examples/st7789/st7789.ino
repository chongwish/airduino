
#include <ST7789v_arduino.h>

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

#define CS_PIN PA4
#define DC_PIN PB1
#define RST_PIN PB0
#define CLK_PIN PA5
#define MOSI_PIN PA7

#define TFT_CS CS_PIN
#define TFT_DC DC_PIN
#define TFT_RST RST_PIN
#define TFT_MOSI MOSI_PIN
#define TFT_SCLK CLK_PIN

ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST, TFT_CS);

void setup(void) {
    tft.init(320, 240);
    tft.setRotation(0);
    tft.fillScreen(BLUE);
}

void loop() {
    tft.fillScreen(RED);
    delay(2000);
    tft.fillScreen(GREEN);
    delay(2000);
}