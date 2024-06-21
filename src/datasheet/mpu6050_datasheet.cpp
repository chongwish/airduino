#include "mpu6050_datasheet.hpp"

const uint8_t Mpu6050DataSheet::MPU_ADDRESS{0x68};
const uint8_t Mpu6050DataSheet::MPU_PWR_MGMT_1{0x6B};
const uint8_t Mpu6050DataSheet::MPU_ACCEL_XOUT_H{0x3B};
const float Mpu6050DataSheet::MPU_RANGE{16384.0};

float Mpu6050DataSheet::convertAccelerometer(int16_t value) {
    return value / MPU_RANGE;
}

float Mpu6050DataSheet::convertGyroscope(int16_t value) {
    return convertAccelerometer(value);
}

float Mpu6050DataSheet::convertTemperature(int16_t value) {
    return value / 340.0 + 36.53;
}
