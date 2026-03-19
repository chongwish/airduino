#include "st7789_7pin.hpp"

namespace soft {

void St7789_7pin::handle(unsigned char oneByte) {
    for (unsigned char i = 0; i < 8; i++) {
        digitalWrite(sck_pin, LOW);
        digitalWrite(sda_pin, (oneByte & 0x80) ? HIGH : LOW);
        oneByte <<= 1;
        digitalWrite(sck_pin, HIGH);
        digitalWrite(sck_pin, LOW);
    }
}

void St7789_7pin::execute(unsigned char instruction) {
    digitalWrite(dc_pin, LOW);
    handle(instruction);
}

inline void St7789_7pin::send(unsigned char data) {
    digitalWrite(dc_pin, HIGH);
    handle(data);
}

inline void St7789_7pin::send2(uint16_t data) {
    digitalWrite(dc_pin, HIGH);
    handle(data & 0xff);
    handle(data >> 8);
}

inline void St7789_7pin::setArea(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2) {
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

void St7789_7pin::initialize() {
    pinMode(sck_pin, OUTPUT);
    pinMode(sda_pin, OUTPUT);
    pinMode(rst_pin, OUTPUT);
    pinMode(dc_pin, OUTPUT);
    pinMode(blk_pin, OUTPUT);

    digitalWrite(sck_pin, HIGH);
    digitalWrite(rst_pin, LOW);
    delay(150);
    digitalWrite(rst_pin, HIGH);
    delay(50);

    // Sleep Out
    execute(0x11);
    delay(100);

    // 65k mode
    execute(0x3A);
    send(0x55);

    // direction
    execute(0x36);
    send(0x00);

    // color invert
    execute(0x21);

    // display on
    execute(0x29);
}

void St7789_7pin::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, const uint16_t &color) {
    setArea(x1, y1, x2, y2);

    for (uint16_t y = y1; y <= y2; ++y) {
        for (uint16_t x = x1; x <= x2; ++x) {
            send2(color);
        }
    }
}

void St7789_7pin::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, Coordinate<uint16_t, uint16_t> &coordinate) {
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

void St7789_7pin::display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, uint16_t (*mapColorFn)(const uint16_t &x, const uint16_t &y)) {
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

}  // namespace soft