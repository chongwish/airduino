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

void St7789_7pin::send(unsigned char data) {
    digitalWrite(dc_pin, HIGH);
    handle(data);
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
    // column
    execute(0x2a);
    send(x1 >> 8);
    send(x1);
    send(x2 >> 8);
    send(x2);

    // row
    execute(0x2b);
    send(y1 >> 8);
    send(y1);
    send(y2 >> 8);
    send(y2);

    execute(0x2C);

    for (uint16_t x = x1; x < x2; ++x) {
        for (uint16_t y = 0; y < y2; ++y) {
            send(color >> 8);
            send(color);
        }
    }
}

}  // namespace soft