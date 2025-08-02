#ifndef AIRDUNIO_DRIVER_TB6612FNG
#define AIRDUNIO_DRIVER_TB6612FNG 1

#include "../airduino.h"
#include "../devices/motor.hpp"

class Tb6612fng : public MotorDriver {
    uint8_t in1_pin, in2_pin, pwm_pin;

public:
    Tb6612fng() = delete;

    Tb6612fng(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin) : in1_pin(in1_pin), in2_pin(in2_pin), pwm_pin(pwm_pin) {}

    void initialize() {
        pinMode(in1_pin, OUTPUT);
        pinMode(in2_pin, OUTPUT);
        pinMode(pwm_pin, OUTPUT);
    }

    void rotateForward(uint8_t speed) {
        digitalWrite(in1_pin, HIGH);
        digitalWrite(in2_pin, LOW);
        analogWrite(pwm_pin, speed);
    }

    void rotateBackward(uint8_t speed) {
        digitalWrite(in1_pin, LOW);
        digitalWrite(in2_pin, HIGH);
        analogWrite(pwm_pin, speed);
    }

    void stop() {
        digitalWrite(in1_pin, LOW);
        digitalWrite(in2_pin, LOW);
        analogWrite(pwm_pin, 0);
    }
};

#endif