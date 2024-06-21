#include "ssd1306.hpp"

void Ssd1306::execute(unsigned char instruction) {
    Wire.beginTransmission(0x3C);
    Wire.write(0x00);
    Wire.write(instruction);
    Wire.endTransmission();
}

void Ssd1306::send(unsigned char data) {
    Wire.beginTransmission(0x3C);
    Wire.write(0x40);
    Wire.write(data);
    Wire.endTransmission();
}

void Ssd1306::initialize() {
#ifdef ARDUINO_ARCH_AIRMCU
    Wire.setSCL(SCL);
    Wire.setSDA(SDA);
#endif
    Wire.begin();

    // turn off oled panel
    execute(0xAE);

    // set low column address
    execute(0x00);

    // set high column address
    execute(0x10);

    // set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    execute(0x40);

    // set contrast control register
    execute(0x81);

    // Set SEG Output Current Brightness
    execute(0xCF);

    // Set SEG/Column Mapping     0xa0 left/righ 0xa1 normal
    execute(0xA1);

    // Set COM/Row Scan Direction   0xc0 top/bottom 0xc8 normal
    execute(0xC8);

    // set normal display
    execute(0xA6);

    // set multiplex ratio(1 to 64)
    execute(0xA8);
    // 1/64 duty
    execute(0x3F);

    // set display offset Shift Mapping RAM Counter (0x00~0x3F)
    execute(0xD3);
    // not offset
    execute(0x00);

    // set display clock divide ratio/oscillator frequency
    execute(0xD5);

    // set divide ratio, Set Clock as 100 Frames/Sec
    execute(0x80);

    // set pre-charge period
    execute(0xD9);

    // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    execute(0xF1);

    // set com pins hardware configuration
    execute(0xDA);
    execute(0x12);

    // set vcomh
    execute(0xDB);

    // Set VCOM Deselect Level
    execute(0x40);

    // Set Page Addressing Mode (0x00/0x01/0x02)
    execute(0x20);
    execute(0x02);

    // set Charge Pump enable/disable
    execute(0x8D);

    // set(0x10) disable
    execute(0x14);

    // Disable Entire Display On (0xa4/0xa5)
    execute(0xA4);

    // Disable Inverse Display On (0xa6/a7)
    execute(0xA6);

    // display ON
    execute(0xAF);

    // color inverted, 0xA6 normal 0xA7
    execute(0xA6);

    // rotation, 0xC8 0xA1 normal 0xC0 0xA0
    execute(0xC8);
    execute(0xA1);
}

void Ssd1306::display(const uint8_t &page_x, const uint8_t &page_y, Coordinate<uint8_t, uint8_t> &coordinate, const uint8_t &size) {
    execute(0xB0 + page_y);
    execute(((page_x & 0xf0) >> 4) | 0x10);
    execute(page_x & 0x0f);
    for (uint8_t i = 0; i < size; i++) {
        send(coordinate.getMark(page_x + i, page_y));
    }
}