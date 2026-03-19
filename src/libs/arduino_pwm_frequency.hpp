#ifndef AIRDUNIO_LIB_ARDUINO_PWM_FREQUENCY
#define AIRDUNIO_LIB_ARDUINO_PWM_FREQUENCY 1

#include "../airduino.h"

class ArduinoPwmFrequency {
    HardwareTimer timer;

public:
    ArduinoPwmFrequency() = delete;

    ArduinoPwmFrequency(TIM_TypeDef *instance) {
        timer.setup(instance);
    }

    void divide(uint32_t value) {
        timer.pause();
        timer.setOverflow(value);
        timer.refresh();
        timer.resume();
    }

    void bind(void (*fn)()) {
    }
};

#endif