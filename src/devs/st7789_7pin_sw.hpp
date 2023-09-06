#include "../libs/display.hpp"

#ifndef AIRDUNIO_DEV_ST7789_7PIN

#define AIRDUNIO_DEV_ST7789_7PIN 1

class St7789_7pin : public Display<uint16_t> {
    public:
        St7789_7pin(uint16_t width, uint16_t height, uint8_t sck_pin, uint8_t sda_pin, uint8_t rst_pin, uint8_t dc_pin, uint8_t blk_pin);
        void begin();
        void refresh();
        void fillPoint(uint16_t x, uint16_t y, uint16_t color);
        void fillBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    private:
        uint8_t sck_pin;
        uint8_t sda_pin;
        uint8_t rst_pin;
        uint8_t dc_pin;
        uint8_t blk_pin;

        void initPin();
        void initDisplay();
        void handle(unsigned char oneByte);
        void execute(unsigned char instruction);
        void send(unsigned char data);
};

#endif