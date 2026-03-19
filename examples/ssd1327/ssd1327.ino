
#include <U8g2lib.h>

#ifdef ARDUINO_ARCH_AIRMCU
#define CS_PIN PA4
#define DC_PIN PB1
#define RST_PIN PB0
#define CLK_PIN PA5
#define MOSI_PIN PA7
#else
#define CS_PIN SS
#define DC_PIN 9
#define RST_PIN 8
#endif

U8G2_SSD1327_WS_128X128_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RST_PIN);

void setup() {
    u8g2.begin();
    u8g2.setDisplayRotation(U8G2_R1);
}

void loop() {
    u8g2.clear();

    u8g2.firstPage();
    do {
        u8g2.drawBox(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
    } while (u8g2.nextPage());

    delay(1000);
}