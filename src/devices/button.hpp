#ifndef AIRDUNIO_DEVICE_BUTTON
#define AIRDUNIO_DEVICE_BUTTON 1

#include "../airduino.h"

class Button {
private:
    uint8_t pin;
    int valid_value;
    int pin_state;

public:
    Button() = delete;
    Button(uint8_t pin, int pin_state, int valid_value) : pin(pin), pin_state(pin_state), valid_value(valid_value) {}

    void initialize() {
        pinMode(pin, pin_state);
    }

    bool isPress() {
        return digitalRead(pin) == valid_value;
    }

    uint8_t getPin() {
        return pin;
    }
};

#endif