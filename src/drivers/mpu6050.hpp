#ifndef AIRDUNIO_DRIVER_MPU6050
#define AIRDUNIO_DRIVER_MPU6050 1

#include <Wire.h>

#include "../airduino.h"
#include "../devices/gyroscope.hpp"

class Mpu6050 : public Gyroscope6AsixDriver {
    const uint8_t MPU_ADDRESS = 0x68;
    const uint8_t MPU_PWR_MGMT_1 = 0x6B;
    const uint8_t MPU_ACCEL_XOUT_H = 0x3B;
    const float MPU_RANGE = 16384.0;
    int16_t temperature;

public:
    void initialize();
    void getRawData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz);

    int16_t getTemperature();
};

#endif