#include "st7789_7pin_sw.hpp"

St7789_7pin::St7789_7pin(uint16_t width, uint16_t height, uint8_t sck_pin, uint8_t sda_pin, uint8_t rst_pin, uint8_t dc_pin, uint8_t blk_pin) :
    sck_pin(sck_pin), sda_pin(sda_pin), rst_pin(rst_pin), dc_pin(dc_pin), blk_pin(blk_pin),
    Display<uint16_t>(width, height) {
}

void St7789_7pin::begin() {
    initPin();
    initDisplay();
}

void St7789_7pin::initPin() {
    pinMode(sck_pin, OUTPUT);
    pinMode(sda_pin, OUTPUT);
    pinMode(rst_pin, OUTPUT);
    pinMode(dc_pin, OUTPUT);
    pinMode(blk_pin, OUTPUT);
}

void St7789_7pin::initDisplay() {
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

inline void St7789_7pin::handle(unsigned char oneByte) {
    for (unsigned char i = 0; i < 8; i++) {
        digitalWrite(sck_pin, LOW);
        digitalWrite(sda_pin, (oneByte & 0x80) ? HIGH : LOW);
        oneByte <<= 1;
        digitalWrite(sck_pin, HIGH);
        digitalWrite(sck_pin, LOW);
    }
}

inline void St7789_7pin::execute(unsigned char instruction) {
    digitalWrite(dc_pin, LOW);
    handle(instruction);
}

inline void St7789_7pin::send(unsigned char data) {
    digitalWrite(dc_pin, HIGH);
    handle(data);
}

void St7789_7pin::refresh() {
}

void St7789_7pin::fillPoint(uint16_t x, uint16_t y, uint16_t color) {
    // column
    execute(0x2a);
    send(x);
    send(x++);
    send(x >> 8);
    send(x);

    // row
    execute(0x2b);
    send(y >> 8);
    send(y++);
    send(y >> 8);
    send(y);
    
    execute(0x2C);
    send(color >> 8);
    send(color);
}

void St7789_7pin::fillBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
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

    for (uint16_t x = x1; x < x2; x++) {
        for (uint16_t y = 0; y < y2; y++) {
            send(color >> 8);
            send(color);
        }
    }
}
