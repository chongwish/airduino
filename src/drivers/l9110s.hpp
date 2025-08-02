#ifndef AIRDUNIO_DRIVER_L9110S
#define AIRDUNIO_DRIVER_L9110S 1

#include "../airduino.h"
#include "../devices/motor.hpp"

class L9110s : public MotorDriver {
    uint8_t ia_pin, ib_pin;

public:
    L9110s() = delete;

    L9110s(uint8_t ia_pin, uint8_t ib_pin) : ia_pin(ia_pin), ib_pin(ib_pin) {}

    void initialize() {
        pinMode(ia_pin, OUTPUT);
        pinMode(ib_pin, OUTPUT);
        stop();
    }

    void rotateForward(uint8_t speed) {
        analogWrite(ib_pin, 0);
        analogWrite(ia_pin, speed);
    }

    void rotateBackward(uint8_t speed) {
        analogWrite(ia_pin, 0);
        analogWrite(ib_pin, speed);
    }

    void stop() {
        analogWrite(ia_pin, 0);
        analogWrite(ib_pin, 0);
    }
};

#endif