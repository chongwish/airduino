#ifndef AIRDUNIO_DRIVER_RZ7889
#define AIRDUNIO_DRIVER_RZ7889 1

#include "../airduino.h"
#include "../devices/motor.hpp"

class Rz7889 : public MotorDriver {
    uint8_t fi_pin, bi_pin;

public:
    Rz7889() = delete;

    Rz7889(uint8_t fi_pin, uint8_t ib_pin) : fi_pin(fi_pin), bi_pin(ib_pin) {}

    void initialize() {
        pinMode(fi_pin, OUTPUT);
        pinMode(bi_pin, OUTPUT);
        stop();
    }

    void rotateForward(uint8_t speed) {
        analogWrite(bi_pin, 0);
        analogWrite(fi_pin, speed);
    }

    void rotateBackward(uint8_t speed) {
        analogWrite(fi_pin, 0);
        analogWrite(bi_pin, speed);
    }

    void stop() {
        analogWrite(fi_pin, 0);
        analogWrite(bi_pin, 0);
    }
};

#endif