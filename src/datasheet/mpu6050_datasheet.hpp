#ifndef AIRDUNIO_DATASHEET_MPU6050
#define AIRDUNIO_DATASHEET_MPU6050 1

#include <stdint.h>

class Mpu6050DataSheet {
    static const uint8_t MPU_ADDRESS;
    static const uint8_t MPU_PWR_MGMT_1;
    static const uint8_t MPU_ACCEL_XOUT_H;
    static const float MPU_RANGE;

public:
    static float convertAccelerometer(int16_t value);
    static float convertGyroscope(int16_t value);
    static float convertTemperature(int16_t value);
};

#endif