#include <devs/mpu6050.hpp>
#include <libs/timer_as_action.hpp>

#include "shake_mpu6050.hpp"

Mpu6050 mpu6050;
TimerAsAction timer_as_action;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t temperature;

void setup() {
  Serial.begin(115200);

  mpu6050.begin();
}

void loop() {
  mpu6050.getRawData(ax, ay, az, gx, gy, gz, temperature);

  timer_as_action.capture([] () -> bool {
    mpu6050.getRawData(ax, ay, az, gx, gy, gz, temperature);
    return shakeCondition(gx, ax, ay);
  });
  resetCondition();
  Serial.println(timer_as_action.getCount());

  delay(10);
}