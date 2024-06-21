#ifndef AIRDUNIO_DRIVER_SSD1306
#define AIRDUNIO_DRIVER_SSD1306 1

#include <Wire.h>

#include "../devices/page_screen.hpp"

class Ssd1306 : public PageScreenDriver<uint8_t, uint8_t> {
    inline void execute(unsigned char instruction);
    inline void send(unsigned char data);

public:
    void initialize();
    void display(const uint8_t &page_x, const uint8_t &page_y, Coordinate<uint8_t, uint8_t> &coordinate, const uint8_t &size) override;
};

#endif