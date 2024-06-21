#ifndef AIRDUNIO_DEVICE_GYROSCOPE
#define AIRDUNIO_DEVICE_GYROSCOPE 1

#include "../airduino.h"

class Gyroscope6AsixDriver : public Driver {
public:
    virtual void getRawData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz) = 0;
};

class Gyroscope6Asix : public Device<Gyroscope6AsixDriver> {
public:
    inline void getRawData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz) {
        driver->getRawData(ax, ay, az, gx, gy, gz);
    }
};

#endif