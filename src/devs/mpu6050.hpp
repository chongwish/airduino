#include "../airduino.h"

#include <Wire.h>

#ifndef AIRDUNIO_DEV_MPU6050

#define AIRDUNIO_DEV_MPU6050 1

class Mpu6050 {
    public:
        void begin();
        inline float convertAccelerometer(int16_t value);
        inline float convertGyroscope(int16_t value);
        inline float convertTemperature(int16_t value);
        void getRawData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz, int16_t &temperature);
    private:
        const uint8_t MPU_ADDRESS = 0x68;
        const uint8_t MPU_PWR_MGMT_1 = 0x6B;
        const uint8_t MPU_ACCEL_XOUT_H = 0x3B;
        const float MPU_RANGE = 16384.0;

        void wakeup();
};

#endif