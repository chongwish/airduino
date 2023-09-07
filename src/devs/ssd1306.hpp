#include "../libs/display.hpp"
#include "../libs/coordinate.hpp"

#include <Wire.h>

#ifndef AIRDUNIO_DEV_SSD1306

#define AIRDUNIO_DEV_SSD1306 1

class Ssd1306 : public Display<uint8_t> {
    public:
        Ssd1306(uint16_t width, uint16_t height);
        void begin();
        void refresh();
        void fillPoint(uint16_t x, uint16_t y, uint8_t color);
        void fillBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    private:
        Coordinate<uint8_t> coordinate;

        void initPin();
        void initDisplay();
        uint8_t calculatePageValue(uint16_t x, uint16_t y, uint8_t value);
        void execute(unsigned char instruction);
        void send(unsigned char data);
};

#endif