#include <devs/mpu6050.hpp>

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t temperature;

Mpu6050 mpu6050;

void setup() {
  Serial.begin(115200);

  mpu6050.begin();
}

void loop() {
  mpu6050.getRawData(ax, ay, az, gx, gy, gz, temperature);

  Serial.print("a/g:\t");
  Serial.print(mpu6050.convertAccelerometer(ax)); Serial.print("\t");
  Serial.print(mpu6050.convertAccelerometer(ay)); Serial.print("\t");
  Serial.print(mpu6050.convertAccelerometer(az)); Serial.print("\t");
  Serial.print(mpu6050.convertGyroscope(gx)); Serial.print("\t");
  Serial.print(mpu6050.convertGyroscope(gy)); Serial.print("\t");
  Serial.print(mpu6050.convertGyroscope(gz)); Serial.print("\t");
  Serial.println(mpu6050.convertTemperature(temperature));

  delay(1000);
}