#include "st7735.hpp"

inline void St7735::execute(unsigned char instruction) {
    digitalWrite(dc_pin, LOW);
    // SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(instruction);
    // SPI.endTransaction();
}

inline void St7735::send(unsigned char data) {
    digitalWrite(dc_pin, HIGH);
    // SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(data);
    // SPI.endTransaction();
}

inline void St7735::send2(uint16_t data) {
    digitalWrite(dc_pin, HIGH);
    SPI.transfer16(data);
}

inline void St7735::setArea(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2) {
    execute(0x2A);
    send(x1);
    send(x1 + 1);
    send(x2);
    send(x2 + 1);

    execute(0x2B);
    send(y1);
    send(y1 + 0x1A);
    send(y2);
    send(y2 + 0x1A);

    execute(0x2C);
}

void St7735::initialize() {
    pinMode(cs_pin, OUTPUT);
    pinMode(dc_pin, OUTPUT);
    pinMode(rst_pin, OUTPUT);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    digitalWrite(rst_pin, LOW);
    delay(100);
    digitalWrite(rst_pin, HIGH);
    delay(50);

    execute(0x11);  // exit sleep;
    delay(150);

    execute(0xB1);
    send(0x05);
    send(0x3A);
    send(0x3A);

    execute(0xB2);
    send(0x05);
    send(0x3A);
    send(0x3A);

    execute(0xB3);
    send(0x05);
    send(0x3A);
    send(0x3A);
    send(0x05);
    send(0x3A);
    send(0x3A);

    execute(0xB4);  // invert
    send(0x03);

    execute(0xC0);
    send(0x62);
    send(0x02);
    send(0x04);

    execute(0xC1);
    send(0xC0);

    execute(0xC2);
    send(0x0D);
    send(0x00);

    execute(0xC3);
    send(0x8D);
    send(0x6A);

    execute(0xC4);
    send(0x8D);
    send(0xEE);

    execute(0xC5); /*VCOM*/
    send(0x0E);

    execute(0x21);

    execute(0xE0);
    send(0x10);
    send(0x0E);
    send(0x02);
    send(0x03);
    send(0x0E);
    send(0x07);
    send(0x02);
    send(0x07);
    send(0x0A);
    send(0x12);
    send(0x27);
    send(0x37);
    send(0x00);
    send(0x0D);
    send(0x0E);
    send(0x10);

    execute(0xE1);
    send(0x10);
    send(0x0E);
    send(0x03);
    send(0x03);
    send(0x0F);
    send(0x06);
    send(0x02);
    send(0x08);
    send(0x0A);
    send(0x13);
    send(0x26);
    send(0x36);
    send(0x00);
    send(0x0D);
    send(0x0E);
    send(0x10);

    execute(0x3A);
    send(0x05);

    execute(0x36);
    send(0xA8);  //

    execute(0x29);
}

void St7735::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, const uint16_t &color) {
    setArea(x1, y1, x2, y2);

    for (uint16_t y = y1; y <= y2; ++y) {
        for (uint16_t x = x1; x <= x2; ++x) {
            send2(color);
        }
    }
}

void St7735::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, Coordinate<uint16_t, uint16_t> &coordinate) {
    setArea(x1, y1, x2, y2);

    uint16_t x_i = 0;
    uint16_t y_i = 0;
    for (uint16_t y = y1; y <= y2; ++y) {
        for (uint16_t x = x1; x <= x2; ++x) {
            send2(coordinate.getMark(x_i, y_i));
            ++x_i;
        }
        x_i = 0;
        ++y_i;
    }
}

void St7735::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, uint16_t (*mapColorFn)(const uint16_t &x, const uint16_t &y)) {
    setArea(x1, y1, x2, y2);

    uint16_t x_i = 0;
    uint16_t y_i = 0;
    for (uint16_t y = y1; y <= y2; ++y) {
        for (uint16_t x = x1; x <= x2; ++x) {
            send2(mapColorFn(x_i, y_i));
            ++x_i;
        }
        x_i = 0;
        ++y_i;
    }
}
