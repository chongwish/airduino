#ifndef AIRDUNIO_DEVICE_MOTOR
#define AIRDUNIO_DEVICE_MOTOR 1

#include "../airduino.h"

class MotorDriver : public Driver {
public:
    virtual void rotateForward(uint8_t speed);
    virtual void rotateBackward(uint8_t speed);
    virtual void stop();
};

class Motor : public Device<MotorDriver> {
public:
    void rotateForward(uint8_t speed) {
        this->driver->rotateForward(speed);
    }

    void rotateBackward(uint8_t speed) {
        this->driver->rotateBackward(speed);
    }

    void stop() {
        this->driver->stop();
    }
};

#endif