#ifndef AIRDUNIO_DRIVER_ST7735
#define AIRDUNIO_DRIVER_SS7735 1

#include <SPI.h>

#include "../airduino.h"
#include "../devices/screen.hpp"
#include "../libs/coordinate.hpp"

class St7735 : public ScreenDriver<uint16_t, uint16_t> {
    SPISettings spi_settings;

    uint8_t cs_pin;
    uint8_t dc_pin;
    uint8_t rst_pin;

    inline void execute(unsigned char instruction);
    inline void send(unsigned char data);
    inline void send2(uint16_t data);
    inline void setArea(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2);

public:
    St7735() = delete;

    St7735(uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin) : cs_pin(cs_pin), dc_pin(dc_pin), rst_pin(rst_pin) {}

    void initialize();

    void display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, const uint16_t &color);
    void display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, Coordinate<uint16_t, uint16_t> &coordinate);
    void display(const uint16_t &x1, const uint16_t &y1, const uint16_t &x2, const uint16_t &y2, uint16_t (*mapColorFn)(const uint16_t &x, const uint16_t &y));
};

#endif