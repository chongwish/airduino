#include <airduino.h>

#include <datasheet/mpu6050_datasheet.hpp>
#include <drivers/mpu6050.hpp>

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t temperature;

Mpu6050 mpu6050;
Gyroscope6Asix gyroscope;

void setup() {
    Serial.begin(115200);

    gyroscope.loadDriver(&mpu6050);
}

void loop() {
    gyroscope.getRawData(ax, ay, az, gx, gy, gz);

    Serial.print("a/g:\t");
    Serial.print(Mpu6050DataSheet::convertAccelerometer(ax));
    Serial.print("\t");
    Serial.print(Mpu6050DataSheet::convertAccelerometer(ay));
    Serial.print("\t");
    Serial.print(Mpu6050DataSheet::convertAccelerometer(az));
    Serial.print("\t");
    Serial.print(Mpu6050DataSheet::convertGyroscope(gx));
    Serial.print("\t");
    Serial.print(Mpu6050DataSheet::convertGyroscope(gy));
    Serial.print("\t");
    Serial.print(Mpu6050DataSheet::convertGyroscope(gz));
    Serial.print("\t");

    uint16_t templerature = mpu6050.getTemperature();
    Serial.println(Mpu6050DataSheet::convertTemperature(temperature));

    delay(1000);
}