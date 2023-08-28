#include "shake_mpu6050.hpp"

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