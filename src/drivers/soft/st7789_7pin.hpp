#ifndef AIRDUNIO_DRIVER_ST7789_7PIN 1
#define AIRDUNIO_DRIVER_ST7789_7PIN 1

#include <Wire.h>

#include "../../airduino.h"
#include "../../devices/screen.hpp"

namespace soft {

class St7789_7pin : public ScreenDriver<uint16_t, uint16_t> {
    uint8_t sck_pin;
    uint8_t sda_pin;
    uint8_t rst_pin;
    uint8_t dc_pin;
    uint8_t blk_pin;

    inline void handle(unsigned char oneByte);
    inline void execute(unsigned char instruction);
    inline void send(unsigned char data);

public:
    St7789_7pin() = delete;

    St7789_7pin(uint8_t sck_pin,
                uint8_t sda_pin,
                uint8_t rst_pin,
                uint8_t dc_pin,
                uint8_t blk_pin) : sck_pin(sck_pin),
                                   sda_pin(sda_pin),
                                   rst_pin(rst_pin),
                                   dc_pin(dc_pin),
                                   blk_pin(blk_pin) {}

    void initialize();

    void display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, const uint16_t &color);
};

}  // namespace soft

#endif