#include <airduino.h>

#include <drivers/mpu6050.hpp>
#include <libs/delay_counter.hpp>

Mpu6050 mpu6050;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t temperature;

bool shake_mpu_back = false;

void resetCondition() {
    shake_mpu_back = false;
}

bool shakeCondition(int16_t gx, int16_t ax, int16_t ay) {
    if (shake_mpu_back != true) {
        if (gx < -30000 && ax > 13000 && ay < 1000) {
            shake_mpu_back = true;
        }
    } else {
        if (gx > 30000 && ax > 13000 && ay < 1000) {
            shake_mpu_back = false;
            return true;
        }
    }
    return false;
}

DelayCounter delay_counter{[]() -> bool {
    mpu6050.getRawData(ax, ay, az, gx, gy, gz);
    return shakeCondition(gx, ax, ay);
}};

void setup() {
    Serial.begin(115200);

    mpu6050.initialize();
}

void loop() {
    mpu6050.getRawData(ax, ay, az, gx, gy, gz);

    resetCondition();
    Serial.println(delay_counter.getCount());

    delay(10);
}