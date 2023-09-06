#include "mpu6050.hpp"

void Mpu6050::begin() {
    Wire.begin();
    
    Wire.beginTransmission(MPU_ADDRESS);

    Wire.write(MPU_PWR_MGMT_1);
    wakeup();

    Wire.endTransmission(true);
}

void Mpu6050::wakeup() {
    Wire.write(0);
}

void Mpu6050::getRawData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz, int16_t &temperature) {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(MPU_ACCEL_XOUT_H);
    Wire.endTransmission(true);

    Wire.requestFrom((size_t)MPU_ADDRESS, (size_t)14, true);

    ax = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    ay = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    az = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) &  0x42 (TEMP_OUT_L)
    gx = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    gy = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    gz = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}

inline float Mpu6050::convertAccelerometer(int16_t value) {
    return value / MPU_RANGE;
}

inline float Mpu6050::convertGyroscope(int16_t value) {
    return convertAccelerometer(value);
}

inline float Mpu6050::convertTemperature(int16_t value) {
    return value / 340.0 + 36.53;
}